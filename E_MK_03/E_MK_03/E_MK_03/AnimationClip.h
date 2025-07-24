#pragma once
#include "Sceneinfo.h"

// ���� �Դϴ�. �� �̷��� ������ �ʿ�� �����ϴ�.
struct Frame
{
    D2D1_RECT_U srcRect;   // ��Ʈ���� �߶� ����

    float        duration; // �� �������� �����Ǵ� �ð�(��)

    float Width() const { return srcRect.right - srcRect.left; }
    float Height() const { return srcRect.bottom - srcRect.top; }

    D2D1_RECT_F ToRectF() const
    {
        return D2D1::RectF(
            static_cast<float>(srcRect.left),
            static_cast<float>(srcRect.top),
            static_cast<float>(srcRect.right),
            static_cast<float>(srcRect.bottom));
    }
};

struct Tag
{
    std::string m_name;
    //std::string which_Scene;
    int m_from;
    int m_to;
    std::string m_direction;
};

// AnimationClip: ������ ������ + �ؽ�ó(immutable)
class AnimationClip
{
public:
    AnimationClip() = default;
    ~AnimationClip() {
        m_frames.clear();
        m_tags.clear();
       // m_sheet ��� comptr�̶� ������ �� 
    };

    // �ؽ�ó ��Ʈ ���� (AssetManager���� �� ���� ȣ��) //�̰ŷ� BITMAP �Ѱ��ִ� �� 
    void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet)
    {
        m_sheet = std::move(sheet);
    }

    // AsepriteParser ��� �������� �� ���� ä�� ����
    void AddFrame(const Frame& frame)
    {
        m_frames.push_back(frame);
        m_totalDuration += frame.duration / 1000.0f;
    }

    void AddTag(const Tag& tag)
    {
        m_tags.push_back(tag);
    }

    void AddSceneInfo(const std::string& info)
    {
        m_sceneInfos.push_back(info);
    }

    const std::vector<std::string>& GetSceneInfos() const
    {
        return m_sceneInfos;
    }

    std::vector<SceneInfo> IntoSceneInfo(std::vector<std::string> parsed) //magic enum �ᵵ �ɵ��� 
    {
        std::vector<SceneInfo> out;
        for (const auto& ind : parsed)
        {
            if (ind == "Title")
            {
                out.push_back(SceneInfo::Title);
                continue;
            }
            else if (ind == "Stage")
            {
                out.push_back(SceneInfo::Stage);
                continue;

            }
            else if (ind == "End")
            {
                out.push_back(SceneInfo::End);
                continue;

            }

            else assert(false);
        }

        return out;
    } 

    // ������ ������ ��ȸ
    const std::vector<Frame>& GetFrames() const { return m_frames; }
    float                       GetTotalDuration() const { return m_totalDuration; }
    ID2D1Bitmap1* GetBitmap() const { return m_sheet.Get(); }

private:
    std::vector<Frame>                  m_frames;
    float                                m_totalDuration = 0.f;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_sheet;
    std::vector<Tag>                    m_tags;
    std::vector<std::string> m_sceneInfos; //�ߺ� ���� ���ʿ� �ε带 �����ϱ� ����. 
};

class SpriteAnimator
{
public:
    SpriteAnimator() = default;

    ~SpriteAnimator() = default;

    bool IsValid() const { return m_clip != nullptr; }

    // ����� Ŭ�� ���� (nullptr ��� �� �÷��� ����)
    void SetCurrentClip(const AnimationClip* clip)
    {
        m_clip = clip;
        m_elapsed = 0.f;
    }
    void SetClip(const AnimationClip* clip)
    {
        m_clip = clip;
        m_elapsed = 0.f;
    }
    // ���� ��� ���� Ŭ�� ��ȸ
    const AnimationClip* GetClip() const { return m_clip; }

    // ���� ���(true) / ��ȸ ���(false)
    void SetLooping(bool loop) { m_loop = loop; }

    void Delete() {  m_clip = nullptr; }

    // deltaTime�� ���ؼ� elapsed ����
    void Update(float deltaTime)
    {
        if (!m_clip) return;
        m_elapsed += deltaTime;

        float total = m_clip->GetTotalDuration(); // ������...
        if (m_loop)
        {
            // ���� ���: elapsed�� total ���� ������
            if (m_elapsed >= total)
                m_elapsed = std::fmod(m_elapsed, total);
        }
        //fmod�� "�ε��Ҽ��� ������(modulo)" �Լ�
        //�ð� ���� �׻�[0.0, total) ������ ����
        else
        {
            // ����� ���: ���� �����ϸ� ����
            if (m_elapsed > total)
                m_elapsed = total;
        }
    }

    // ���� ��� ���� ������ �ε��� ��ȸ
    const Frame& GetCurrentFrame() const //��� ������ ���⼭ �ϴ� �� �ɶ� 
    {
        static Frame dummy{ {0,0,0,0}, 0.f };

        if (!m_clip || m_clip->GetFrames().empty())
            return dummy;

        float accum = 0.f;
        for (auto& frame : m_clip->GetFrames())
        {
            accum += frame.duration / 1000.0f;
            if (m_elapsed < accum)
            {
//                std::cout << m_elapsed << " " << std::endl;
                return frame;
            }
        }
        // elapsed�� totalDuration �̻��� �� ������ ������ ��ȯ
        return m_clip->GetFrames().back();
    }

    // ��� ��ġ(��) ��ȸ/����
    float GetElapsed() const { return m_elapsed; }
    void  SetElapsed(float t) { m_elapsed = t; }

private:
    const AnimationClip* m_clip = nullptr;  // immutable clip ������
    float                m_elapsed = 0.f;      // ��� ��ġ
    bool                 m_loop = true;     // ���� ��� ����
};
#pragma once
