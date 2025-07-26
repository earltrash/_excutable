#pragma once
#include "pch.h"
#include "AnimationClip.h" 
#include "AsepriteParser.h"
#include "Renderer.h"

using namespace std;

using wsg = std::wstring;
//using path = std::filesystem::path;
using path = std::filesystem::path;
using rd = std::shared_ptr<D2DRenderer>;

//1. Scene������  asset�ҷ����� ����
//2. asset ���� ����
//3. 


struct Clip_Asset {
    std::string Name;              
    std::string Ani_Name;           
    AnimationClip clip;              
    std::vector<string> whichScene;
};


class ResourceManager //Core Initalize �ܰ迡�� Asset ���ε� �ϱ� ��. ��� asset�� ���� Core Pointer �� �Ѱ��ֱ⸸ �ϸ� �Ǵϱ� unorded_map 
{
    using AnimationClips = std::vector<std::pair<std::string, AnimationClip>>; //obj�� clip�� ����. 
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    //static ResourceManager& Get();
    void AssetLoad(rd renderer, const std::string& directory);
    void LoadTexture(rd renderer, wsg name, path path);

    ComPtr<ID2D1Bitmap1> GetTexture(const string& Info);
    void RegisterClip(const Clip_Asset& asset);
    std::vector<Clip_Asset> GetClips(const string& Info);

    void Clean();

    std::string GetAbsoluteResourcePathA();

private:
    AsepriteParser ap;
    std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_textures;
    std::wstring to_wstring_hash(const std::string& s);
    //�� ���� ���ļ� ���� ������. Scene -> Name -> Asset ������

    std::unordered_map<std::string, Clip_Asset> allClipAssets; 
    std::unordered_map<string, std::vector<std::string>> sceneToClipKeys;
};