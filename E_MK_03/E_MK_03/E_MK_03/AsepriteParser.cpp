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
    std::vector<Clip_Asset> assets; // 여러 클립을 담을 벡터

    if (!ifs.is_open())
        std::cerr << "파일을 열 수 없습니다.\n";

    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    auto parsed = nlohmann::json::parse(content, nullptr, false);

    if (parsed.is_discarded())
        std::cerr << "JSON 파싱 실패: 유효하지 않은 문서입니다.\n";

    const auto& root = parsed;

    // 전체 프레임 먼저 파싱
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

    // Scene 정보 파싱
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

    // 각 태그별로 별도의 Clip_Asset 생성
    if (root["meta"].contains("frameTags"))
    {
        for (const auto& t : root["meta"]["frameTags"])
        {
            Clip_Asset asset; // 각 태그마다 새로운 Asset 생성

            asset.Name = jsonPath.stem().string(); // 파일명
            asset.Ani_Name = t["name"]; // "Idle", "Walk", "Run" 등
            asset.whichScene = sceneInfo; // Scene 정보 복사

            Tag tag;
            tag.m_from = t["from"];
            tag.m_to = t["to"];
            tag.m_direction = t["direction"];

            asset.clip.AddTag(tag);

            // 해당 태그 범위의 프레임만 추가
            for (int i = tag.m_from; i <= tag.m_to; ++i) {
                if (i < allFrames.size()) {
                    asset.clip.AddFrame(allFrames[i]);
                }
            }

            assets.push_back(asset); // 벡터에 추가
        }
    }

    return assets;
}





