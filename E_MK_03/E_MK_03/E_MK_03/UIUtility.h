#pragma once
#include "SimpleMathHelper.h"

using Vec2 = MYHelper::Vector2F;

struct Rect
{
    float x, y, width, height;
    Rect(float x = 0, float y = 0, float w = 0, float h = 0) : x(x), y(y), width(w), height(h) {}

    bool Contains(const Vec2& point) const
    {
        return point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height;
    }

    D2D1_RECT_F ToD2DRect() const
    {
        return D2D1::RectF(x, y, x + width, y + height);
    }
};

// SafeRelease 매크로 (COM 객체 해제용)
template <class T>
inline void SafeRelease(T** ppT)
{
    if (*ppT != nullptr)
    {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}

// 파일 읽기 위해서.
inline std::wstring ToWString(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}