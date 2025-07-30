#pragma once
#include "pch.h"
#include "SimpleMathHelper.h"
#include "UIUtility.h"

// WIC ���丮 ���� ���� (�� ���� ����)
extern IWICImagingFactory* g_pWICFactory;

// WIC ���丮 �ʱ�ȭ �Լ� (���� �ʱ�ȭ �� ȣ��)
void InitializeWIC();

// WIC ���丮 ���� �Լ� (���� ���� �� ȣ��)
void ReleaseWIC();

// ��Ʈ�� ������
class BitmapManager
{
public:
    BitmapManager(ID2D1RenderTarget* rt) : renderTarget(rt) {}

    // ���� ���Ͽ��� ��Ʈ���� �ε��ϴ� ����
    bool LoadBitmap(const std::string& filename, const std::string& key)
    {
        if (bitmaps.count(key) != 0) return true; // �̹� �ε��

        ID2D1Bitmap* newBitmap = nullptr;
        HRESULT hr = S_OK;

        IWICBitmapDecoder* pDecoder = nullptr;
        IWICBitmapFrameDecode* pSource = nullptr;
        IWICFormatConverter* pConverter = nullptr;

        // ���� ��θ� ���̵� ���ڿ��� ��ȯ
        std::wstring wFilename = ToWString(filename);
        //std::string sFilename(wFilename.begin(), wFilename.end());
        //std::cout << "[BitmapManager] ��Ʈ�� �ε� �õ�: " << sFilename << " (Ű: " << key << ")" << std::endl;
        //std::cout << "[BitmapManager] renderTarget �ּ�: 0x" << std::hex << (uintptr_t)renderTarget << std::dec << std::endl;

        // 1. WIC ���ڴ� ����
        hr = g_pWICFactory->CreateDecoderFromFilename(
            wFilename.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        // 2. ù ��° ������ ��������
        if (SUCCEEDED(hr))
        {
            hr = pDecoder->GetFrame(0, &pSource);
        }

        // 3. ���� ������ ����
        if (SUCCEEDED(hr))
        {
            hr = g_pWICFactory->CreateFormatConverter(&pConverter);
        }

        // 4. ���� ������ �ʱ�ȭ
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

        // 5. Direct2D ��Ʈ�� ����
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
            //// ���� �� ���� ��Ʈ�� ���� (�׽�Ʈ��)
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

    ~BitmapManager() // �Ҹ��ڿ��� ��Ʈ�� �ڿ� ����
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

