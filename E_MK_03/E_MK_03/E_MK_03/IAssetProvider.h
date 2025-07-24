#pragma once
#include "pch.h"
#include "ResourceManager.h"
#include "Sceneinfo.h"

class IAssetProvider
{
public:
    virtual ComPtr<ID2D1Bitmap1> GetTexture(const SceneInfo& Info) = 0;
    virtual  std::vector<Clip_Asset> GetClips(const SceneInfo& Info) = 0;
    virtual ~IAssetProvider() {}


};