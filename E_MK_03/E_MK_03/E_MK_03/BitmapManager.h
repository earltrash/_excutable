#pragma once
#include "pch.h"
#include "SimpleMathHelper.h"
#include "UIUtility.h"

// WIC 팩토리 전역 변수 (한 번만 생성)
extern IWICImagingFactory* g_pWICFactory;

// WIC 팩토리 초기화 함수 (엔진 초기화 시 호출)
void InitializeWIC();

// WIC 팩토리 해제 함수 (엔진 종료 시 호출)
void ReleaseWIC();

// 비트맵 관리자
class BitmapManager
{
public:
    BitmapManager(ID2D1RenderTarget* rt) : renderTarget(rt) {}

    // 실제 파일에서 비트맵을 로드하는 로직
    bool LoadBitmap(const std::string& filename, const std::string& key)
    {
        if (bitmaps.count(key) != 0) return true; // 이미 로드됨

        ID2D1Bitmap* newBitmap = nullptr;
        HRESULT hr = S_OK;

        IWICBitmapDecoder* pDecoder = nullptr;
        IWICBitmapFrameDecode* pSource = nullptr;
        IWICFormatConverter* pConverter = nullptr;

        // 파일 경로를 와이드 문자열로 변환
        std::wstring wFilename = ToWString(filename);
        //std::string sFilename(wFilename.begin(), wFilename.end());
        //std::cout << "[BitmapManager] 비트맵 로드 시도: " << sFilename << " (키: " << key << ")" << std::endl;
        //std::cout << "[BitmapManager] renderTarget 주소: 0x" << std::hex << (uintptr_t)renderTarget << std::dec << std::endl;

        // 1. WIC 디코더 생성
        hr = g_pWICFactory->CreateDecoderFromFilename(
            wFilename.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        // 2. 첫 번째 프레임 가져오기
        if (SUCCEEDED(hr))
        {
            hr = pDecoder->GetFrame(0, &pSource);
        }

        // 3. 포맷 컨버터 생성
        if (SUCCEEDED(hr))
        {
            hr = g_pWICFactory->CreateFormatConverter(&pConverter);
        }

        // 4. 포맷 컨버터 초기화
        if (SUCCEEDED(hr))
        {
            hr = pConverter->Initialize(
                pSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.f,
                WICBitmapPaletteTypeCustom
            );
        }

        // 5. Direct2D 비트맵 생성
        if (SUCCEEDED(hr))
        {
            hr = renderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                nullptr,
                &newBitmap
            );
        }

        SafeRelease(&pDecoder);
        SafeRelease(&pSource);
        SafeRelease(&pConverter);

        if (SUCCEEDED(hr) && newBitmap)
        {
            bitmaps[key] = newBitmap;
            return true;
        }
        else
        {
            return false;
            //// 실패 시 더미 비트맵 생성 (테스트용)
            //hr = renderTarget->CreateBitmap(D2D1::SizeU(48, 48), D2D1::BitmapProperties(), &newBitmap);
            //if (SUCCEEDED(hr) && newBitmap)
            //{
            //    bitmaps[key] = newBitmap;
            //    return true;
            //}
        }
        
    }

    ID2D1Bitmap* GetBitmap(const std::string& key)
    {
        auto it = bitmaps.find(key);
        return it != bitmaps.end() ? it->second : nullptr;
    }

    ~BitmapManager() // 소멸자에서 비트맵 자원 해제
    {
        for (auto& pair : bitmaps)
        {
            SafeRelease(&pair.second);
        }
        bitmaps.clear();
    }

private:
    std::unordered_map<std::string, ID2D1Bitmap*> bitmaps;
    ID2D1RenderTarget* renderTarget;
};

