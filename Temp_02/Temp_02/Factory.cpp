#pragma once
#include "Factory.h"
#include "ObjFactory.h"
#include "Button.h"
#include "Player.h"
#include "SceneManager.h"

////////////////////
#include "Potion.h"
#include "Material.h"
#include "Wearable.h"
#include "Enchancer.h"
#include "json.hpp"
///////////////////////////
#include <fstream>       // ifstream
#include <filesystem>    // std::filesystem


using json = nlohmann::json;


void LoadItemsFromJson(const std::string& path)
{
    
        std::ifstream file(path); //
        std::cout << "현재 경로: " << std::filesystem::current_path() << std::endl;

        json j;
        file >> j;
        int times = 0;
        for (const auto& itemData : j["items"]) {
        
            std::string type = itemData["type"];
            std::string moment = itemData["Moment"];
            cout << moment << endl;
            ItemCommonData common = {
                itemData["id"],
                itemData["name"],
                itemData["description"],
                itemData["enchantable"],
                itemData["synthesizable"],
                (StringToNM(moment))
            };
            std::cout << j["description"] << std::endl;
            //디버깅이 어려워 질 수도 있겠는데, 만들어지는 순간에 타입이 결정됨.
            ObjFactory::Get().RegisterObject(common.name, [=]() -> std::unique_ptr<Object> {
                if (type == "Potion")
                    return std::make_unique<Potion>(common, itemData);
                else if (type == "Enchancer")
                    return std::make_unique<Enchancer>(common, itemData);
                else if (type == "Wearable")
                    return std::make_unique<Wearable>(common, itemData);
                else if (type == "Material")
                    return std::make_unique<Material>(common, itemData);
                else {
                    std::cerr << "Unknown type: " << type << "\n";
                    return nullptr;
                }
                });
        }
}

void ObjectRegister()
{
     LoadItemsFromJson("../OBJ_Json/item.json"); //해당 경로의 json을 읽어서 아이템 스텟 파싱 및 생성


    ObjFactory::Get().RegisterObject("Start", []() {
        return std::make_unique<Button>(
            RECT{ 600, 300, 1000, 500 },
            [](const MSG& msg) {
                SceneManager::Get().ChangeScene("Stage");
            });
        });

    ObjFactory::Get().RegisterObject("Exit", []() {
        return std::make_unique<Button>(
            RECT{ 600, 600, 1000, 800 },
            [](const MSG& msg) {
                PostQuitMessage(0);
            });
        });







    ObjFactory::Get().RegisterObject("Player", []() {
        return std::make_unique<Player>(
            RECT{ 600, 300, 1000, 500 }
        );
        });

}






