#pragma once
#include "Sceneinfo.h"

// 예시 입니다. 꼭 이렇게 구현할 필요는 없습니다.
struct Frame
{
    D2D1_RECT_U srcRect;   // 시트에서 잘라낼 영역

    float        duration; // 이 프레임이 유지되는 시간(초)

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

// AnimationClip: 프레임 데이터 + 텍스처(immutable)
class AnimationClip
{
public:
    AnimationClip() = default;
    ~AnimationClip() {
        m_frames.clear();
        m_tags.clear();
       // m_sheet 얘는 comptr이라 괜찮을 듯 
    };

    // 텍스처 시트 연결 (AssetManager에서 한 번만 호출) //이거로 BITMAP 넘겨주는 듯 
    void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet)
    {
        m_sheet = std::move(sheet);
    }

    // AsepriteParser 등에서 프레임을 한 번만 채워 넣음
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

    std::vector<SceneInfo> IntoSceneInfo(std::vector<std::string> parsed) //magic enum 써도 될듯함 
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

    // 프레임 데이터 조회
    const std::vector<Frame>& GetFrames() const { return m_frames; }
    float                       GetTotalDuration() const { return m_totalDuration; }
    ID2D1Bitmap1* GetBitmap() const { return m_sheet.Get(); }

private:
    std::vector<Frame>                  m_frames;
    float                                m_totalDuration = 0.f;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_sheet;
    std::vector<Tag>                    m_tags;
    std::vector<std::string> m_sceneInfos; //중복 에셋 불필요 로드를 방지하기 위함. 
};

class SpriteAnimator
{
public:
    SpriteAnimator() = default;

    ~SpriteAnimator() = default;

    bool IsValid() const { return m_clip != nullptr; }

    // 재생할 클립 설정 (nullptr 허용 → 플레이 중지)
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
    // 현재 재생 중인 클립 조회
    const AnimationClip* GetClip() const { return m_clip; }

    // 루프 재생(true) / 단회 재생(false)
    void SetLooping(bool loop) { m_loop = loop; }

    void Delete() {  m_clip = nullptr; }

    // deltaTime을 더해서 elapsed 갱신
    void Update(float deltaTime)
    {
        if (!m_clip) return;
        m_elapsed += deltaTime;

        float total = m_clip->GetTotalDuration(); // 다형성...
        if (m_loop)
        {
            // 루프 모드: elapsed를 total 범위 안으로
            if (m_elapsed >= total)
                m_elapsed = std::fmod(m_elapsed, total);
        }
        //fmod는 "부동소수점 나머지(modulo)" 함수
        //시간 값을 항상[0.0, total) 범위로 유지
        else
        {
            // 논루프 모드: 끝에 도달하면 고정
            if (m_elapsed > total)
                m_elapsed = total;
        }
    }

    // 현재 재생 중인 프레임 인덱스 조회
    const Frame& GetCurrentFrame() const //사실 갱신은 여기서 하는 거 걸랑 
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
        // elapsed가 totalDuration 이상일 땐 마지막 프레임 반환
        return m_clip->GetFrames().back();
    }

    // 재생 위치(초) 조회/설정
    float GetElapsed() const { return m_elapsed; }
    void  SetElapsed(float t) { m_elapsed = t; }

private:
    const AnimationClip* m_clip = nullptr;  // immutable clip 데이터
    float                m_elapsed = 0.f;      // 재생 위치
    bool                 m_loop = true;     // 루프 재생 여부
};
#pragma once
