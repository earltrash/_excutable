#pragma once
#include "pch.h"
#include <sstream>
#include <fstream>
#include "json.hpp"
#include "AsepriteParser.h"
#include "assert.h"
#include <filesystem>
#include "ResourceManager.h"


using Filepath = std::filesystem::path;

Clip_Asset AsepriteParser::Load(Filepath& jsonPath)
{
    std::ifstream ifs(jsonPath);
    Frame fd;
    Clip_Asset Asset; 

    if (!ifs.is_open())
        std::cerr << "������ �� �� �����ϴ�.\n";

    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    auto parsed = nlohmann::json::parse(content, nullptr, false);  // ������ ���� 'false'�� ���� ��Ȱ��ȭ

    if (parsed.is_discarded())
        std::cerr << "JSON �Ľ� ����: ��ȿ���� ���� �����Դϴ�.\n";

    const auto& root = parsed;
    //std::string sceneInfo = root.value("SceneInfo", "Unknown");


    auto& framesNode = root["frames"];
    if (framesNode.is_object())
    {
        for (auto it = framesNode.begin(); it != framesNode.end(); ++it)
        {
            const auto& f = it.value();
            fd.srcRect.left = f["frame"]["x"];
            fd.srcRect.top = f["frame"]["y"];
            fd.srcRect.right = f["frame"]["x"].get<UINT32>() + f["frame"]["w"].get<UINT32>();
            fd.srcRect.bottom = f["frame"]["y"].get<UINT32>() + f["frame"]["h"].get<UINT32>();
            fd.duration = f["duration"];
            Asset.clip.AddFrame(fd);
        }
    }
    else if (framesNode.is_array())
    {
        for (const auto& f : framesNode)
        {
            fd.srcRect.left = f["frame"]["x"];
            fd.srcRect.top = f["frame"]["y"];
            fd.srcRect.right = f["frame"]["x"].get<UINT32>() + f["frame"]["w"].get<UINT32>();
            fd.srcRect.bottom = f["frame"]["y"].get<UINT32>() + f["frame"]["h"].get<UINT32>();
            fd.duration = f["duration"];
            Asset.clip.AddFrame(fd);
        }
    }

    if (root["meta"].contains("frameTags"))
    {
        std::vector<Frame> allFrames = Asset.clip.GetFrames(); // ���� clip���� ������ ��ü ������ ���

        for (const auto& t : root["meta"]["frameTags"])
        {
            Tag tag;
            Asset.Ani_Name = t["name"]; //idle 
            tag.m_from = t["from"];
            tag.m_to = t["to"];
            tag.m_direction = t["direction"];



            std::string sceneInfo;
            if (root.contains("SceneInfo")) {
                if (root["SceneInfo"].is_array()) {
                    for (const auto& sceneStr : root["SceneInfo"]) {
                        Asset.whichScene.push_back(sceneStr.get<std::string>());
                    }
                }
                else if (root["SceneInfo"].is_string()) {
                    Asset.whichScene.push_back(root["SceneInfo"].get<std::string>());
                }
            }
            Asset.Name = jsonPath.stem().string();
            Asset.clip.AddTag(tag);
           

            for (int i = tag.m_from; i <= tag.m_to; ++i)
                Asset.clip.AddFrame(allFrames[i]);      
        }
    }

    return Asset;
}






