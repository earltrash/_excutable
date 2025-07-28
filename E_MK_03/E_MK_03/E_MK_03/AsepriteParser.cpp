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

std::vector<Clip_Asset> AsepriteParser::Load(Filepath& jsonPath)
{
    std::ifstream ifs(jsonPath);
    Frame fd;
    std::vector<Clip_Asset> assets; // ���� Ŭ���� ���� ����

    if (!ifs.is_open())
        std::cerr << "������ �� �� �����ϴ�.\n";

    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    auto parsed = nlohmann::json::parse(content, nullptr, false);

    if (parsed.is_discarded())
        std::cerr << "JSON �Ľ� ����: ��ȿ���� ���� �����Դϴ�.\n";

    const auto& root = parsed;

    // ��ü ������ ���� �Ľ�
    std::vector<Frame> allFrames;
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
            allFrames.push_back(fd);
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
            allFrames.push_back(fd);
        }
    }

    // Scene ���� �Ľ�
    std::vector<std::string> sceneInfo;
    if (root.contains("SceneInfo")) {
        if (root["SceneInfo"].is_array()) {
            for (const auto& sceneStr : root["SceneInfo"]) {
                sceneInfo.push_back(sceneStr.get<std::string>());
            }
        }
        else if (root["SceneInfo"].is_string()) {
            sceneInfo.push_back(root["SceneInfo"].get<std::string>());
        }
    }

    // �� �±׺��� ������ Clip_Asset ����
    if (root["meta"].contains("frameTags"))
    {
        for (const auto& t : root["meta"]["frameTags"])
        {
            Clip_Asset asset; // �� �±׸��� ���ο� Asset ����

            asset.Name = jsonPath.stem().string(); // ���ϸ�
            asset.Ani_Name = t["name"]; // "Idle", "Walk", "Run" ��
            asset.whichScene = sceneInfo; // Scene ���� ����

            Tag tag;
            tag.m_from = t["from"];
            tag.m_to = t["to"];
            tag.m_direction = t["direction"];

            asset.clip.AddTag(tag);

            // �ش� �±� ������ �����Ӹ� �߰�
            for (int i = tag.m_from; i <= tag.m_to; ++i) {
                if (i < allFrames.size()) {
                    asset.clip.AddFrame(allFrames[i]);
                }
            }

            assets.push_back(asset); // ���Ϳ� �߰�
        }
    }

    return assets;
}





