#include "pch.h"
#include "ResourceManager.h"
#include <filesystem>

class D2DRenderer;
using namespace std;

void ResourceManager::AssetLoad(rd renderer, const std::string& directory)
{
    namespace fs = std::filesystem;
    fs::path base = fs::current_path();
    fs::path resourcePath = base.parent_path() / "Resource";

    std::cout << "���ҽ� ���: " << resourcePath << std::endl;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(resourcePath, fs::directory_options::skip_permission_denied)) {
            try {
                if (entry.is_regular_file()) {
                    std::cout << "path: " << entry.path().string() << std::endl;

                    if (entry.path().extension() == ".json") {
                        std::string filename = entry.path().stem().string();
                        std::wstring fullPath = entry.path().wstring();

                        std::cout << "name: " << filename << std::endl;
                        wsg name = wsg(filename.begin(), filename.end());
                        LoadTexture(renderer, name, fullPath);
                    }
                }
            }
            catch (const std::exception& e) {
                std::cerr << "���� ó�� �� ����: " << e.what() << std::endl;
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "���丮 ��ȸ ����: " << e.what() << std::endl;
    }

}


void ResourceManager::LoadTexture(rd renderer, wsg name, path Path)
{
    if (!renderer)
        std::wcout << "������ ����" << std::endl;


    Clip_Asset clips = ap.Load(Path); // json �Ľ��� string ���
    std::filesystem::path imagePath = Path; // �� wstring ��� path
    imagePath.replace_extension(L".png");

    std::wcout << "�̹��� ���: " << imagePath << std::endl;

    if (!std::filesystem::exists(imagePath)) {
        std::wcerr << "[����] �̹��� ���� �������� ����: " << imagePath << std::endl;
        return;
    }

    ComPtr<ID2D1Bitmap1> newBitmap;
    renderer->CreateBitmapFromFile(imagePath.c_str(), newBitmap.GetAddressOf());
    m_textures[name] = newBitmap;

    clips.clip.SetBitmap(newBitmap);
    RegisterClip(clips); //�� Scene���� �̷��� �ϱ� ��. 

}

ComPtr<ID2D1Bitmap1> ResourceManager::GetTexture(const string& Info)
{
    return nullptr;
}

std::vector<Clip_Asset> ResourceManager::GetClips(const string& Info)
{
    std::vector<Clip_Asset> Out;

    // Info�� �ش��ϴ� Ű ����� �ִ��� Ȯ��
    auto it = sceneToClipKeys.find(Info);
    if (it != sceneToClipKeys.end())
    {
        const std::vector<std::string>& keys = it->second;

        for (const auto& key : keys)
        {
            auto assetIt = allClipAssets.find(key);
            if (assetIt != allClipAssets.end())
            {
                Out.push_back(assetIt->second);
            }
            else
            {
                std::cout << "[���] Ű�� �ش��ϴ� �ּ��� ����: " << key << std::endl;
            }
        }
    }

    return Out;


}

void ResourceManager::Clean()
{
   //�ϴ� ������ ��... Ȥ���� �𸣴ϱ� 

}

std::string ResourceManager::GetAbsoluteResourcePathA()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);

    std::filesystem::path path(exePath);
    path = path.parent_path();   // exe ��ġ
    path /= "Resource";          // ���� ���� �� Resource

    return path.string();
}







void ResourceManager::RegisterClip(const Clip_Asset& asset)
{
    std::string uniqueKey = asset.Name + "_" + std::to_string(std::hash<std::string>{}(asset.Ani_Name));
    allClipAssets[uniqueKey] = asset;

    for (std::string info : asset.whichScene) {
        sceneToClipKeys[info].push_back(uniqueKey);
    }
}

std::wstring ResourceManager::to_wstring_hash(const std::string& s)
{
    std::hash<std::string> hasher;
    return std::to_wstring(hasher(s));
}






