#pragma once
#include "pch.h"
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
    int m_from;
    int m_to;
    std::string m_direction;
};

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

