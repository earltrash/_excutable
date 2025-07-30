#include "pch.h"


// WIC 팩토리 전역 변수 정의
IWICImagingFactory* g_pWICFactory = nullptr;

// WIC 팩토리 초기화 함수
void InitializeWIC()
{
    //wchar_t wbuffer[MAX_PATH];
    //DWORD dwRet = GetCurrentDirectoryW(MAX_PATH, wbuffer);
    //if (dwRet > 0 && dwRet < MAX_PATH)
    //{
    //    // wchar_t* (UTF-16)을 char* (UTF-8 또는 시스템 기본 코드 페이지)로 변환
    //    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, nullptr, 0, nullptr, nullptr);
    //    if (bufferSize > 0)
    //    {
    //        std::string sbuffer(bufferSize, 0); // null terminator 포함하여 버퍼 생성
    //        WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, &sbuffer[0], bufferSize, nullptr, nullptr);
    //        // WideCharToMultiByte가 마지막에 null terminator를 포함하므로, sbuffer의 크기를 1 줄여서 불필요한 null 문자를 제거합니다.
    //        sbuffer.pop_back();
    //        std::cout << "[DEBUG] 현재 작업 디렉토리: " << sbuffer << std::endl;
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
        std::cout << "WIC Factory 초기화 실패" << std::endl;
    }
}

// WIC 팩토리 해제 함수
void ReleaseWIC()
{
    SafeRelease(&g_pWICFactory);
}
