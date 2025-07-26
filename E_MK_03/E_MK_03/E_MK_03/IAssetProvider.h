#pragma once
#include "pch.h"
#include "ResourceManager.h"

class IAssetProvider //ResourceManager�� ���� ���� ���ϱ� ����
{
public:
    virtual ComPtr<ID2D1Bitmap1> GetTexture(const  std::string& Info) = 0;
    virtual  std::vector<Clip_Asset> GetClips(const  std::string& Info) = 0;
    virtual ~IAssetProvider() {}
};