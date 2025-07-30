#include "pch.h"


// WIC ���丮 ���� ���� ����
IWICImagingFactory* g_pWICFactory = nullptr;

// WIC ���丮 �ʱ�ȭ �Լ�
void InitializeWIC()
{
    //wchar_t wbuffer[MAX_PATH];
    //DWORD dwRet = GetCurrentDirectoryW(MAX_PATH, wbuffer);
    //if (dwRet > 0 && dwRet < MAX_PATH)
    //{
    //    // wchar_t* (UTF-16)�� char* (UTF-8 �Ǵ� �ý��� �⺻ �ڵ� ������)�� ��ȯ
    //    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, nullptr, 0, nullptr, nullptr);
    //    if (bufferSize > 0)
    //    {
    //        std::string sbuffer(bufferSize, 0); // null terminator �����Ͽ� ���� ����
    //        WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, &sbuffer[0], bufferSize, nullptr, nullptr);
    //        // WideCharToMultiByte�� �������� null terminator�� �����ϹǷ�, sbuffer�� ũ�⸦ 1 �ٿ��� ���ʿ��� null ���ڸ� �����մϴ�.
    //        sbuffer.pop_back();
    //        std::cout << "[DEBUG] ���� �۾� ���丮: " << sbuffer << std::endl;
    //    }
    //}

    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&g_pWICFactory)
    );

    if (FAILED(hr))
    {
        std::cout << "WIC Factory �ʱ�ȭ ����" << std::endl;
    }
}

// WIC ���丮 ���� �Լ�
void ReleaseWIC()
{
    SafeRelease(&g_pWICFactory);
}
