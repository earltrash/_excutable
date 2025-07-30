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


//////////////////////////////
// 시작화면 - TitleScen
     ObjFactory::Get().RegisterObject("시작화면_0", []() {
         // 버튼 -> bg
         return std::make_unique<Button>(
             RECT{ 0, 0, 1920,  1080},
             [](const MSG& msg) {
                 //cout << "background" << endl;
             });
         });


     ObjFactory::Get().RegisterObject("시작화면_1", []() {
          // 버튼 -> bg
         return std::make_unique<Button>(
             RECT{ 147, 254, 147 + 702,  254 + 83 },
             [](const MSG& msg) {
                 cout << "싱클레어 가 히스토리" << endl;
             });
         });


     ObjFactory::Get().RegisterObject("시작화면_2", []() {
         int x = 147;
         int y = 564;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 75},
             [](const MSG& msg) {
                 cout << "게임 시작합니다." << endl;
                 SceneManager::Get().ChangeScene("Outgame");
             });
         });


     ObjFactory::Get().RegisterObject("시작화면_3", []() {
         int x = 147;
         int y = 697;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 75 },
             [](const MSG& msg) {
                 cout << "설정창을 킵/끕니다." << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });


     ObjFactory::Get().RegisterObject("시작화면_4", []() {
         int x = 147;
         int y = 830;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 75 },
             [](const MSG& msg) {
                 cout << "크레딧창을 킵/끕니다." << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });


//////////////////////////////
// 아웃게임 - Outgame
     //ObjFactory::Get().RegisterObject("시작화면_0", []() {
     //    // 버튼 -> bg
     //    // 배경 일단 회색임 그거 시작화면이랑 같으니까 추가 안함
     //    return std::make_unique<Button>(
     //        RECT{ 0, 0, 1920,  1080 },
     //        [](const MSG& msg) {
     //        });
     //    });

     
         

     ObjFactory::Get().RegisterObject("아웃게임_1", []() {
         int x = 455;
         int y = 772;
         return std::make_unique<Button>(
             RECT{ x, y, x + 1010, y + 207 },
             [](const MSG& msg) {
                 cout << "텍스트 박스" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });

     ObjFactory::Get().RegisterObject("아웃게임_2", []() {
         int x = 503;
         int y = 805;
         return std::make_unique<Button>(
             RECT{ x, y, x + 218, y + 41 },
             [](const MSG& msg) {
                 cout << "싱클레어 N세 이름" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });
     ObjFactory::Get().RegisterObject("아웃게임_3", []() {
         int x = 503;
         int y = 869;
         return std::make_unique<Button>(
             RECT{ x, y, x + 304, y + 59 },
             [](const MSG& msg) {
                 cout << "텍스트 내용" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });
     ObjFactory::Get().RegisterObject("아웃게임_4", []() {
         int x = 1087;
         int y = 921;
         return std::make_unique<Button>(
             RECT{ x, y, x + 140, y + 40 },
             [](const MSG& msg) {
                 cout << "예 (수락 버튼)" << endl;
                 SceneManager::Get().ChangeScene("Ingame");
             });
         });
     ObjFactory::Get().RegisterObject("아웃게임_5", []() {
         int x = 1280;
         int y = 921;
         return std::make_unique<Button>(
             RECT{ x, y, x + 140, y + 40 },
             [](const MSG& msg) {
                 cout << "아니오 (거절 버튼)" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });

//////////////////////////////
// 인게임 - Ingame
     ObjFactory::Get().RegisterObject("인게임_1", []() {
         int x = 64;
         int y = 57;
         return std::make_unique<Button>(
             RECT{ x, y, x + 37, y + 37 },
             [](const MSG& msg) {
                 cout << "아웃게임 이동 버튼" << endl;
                 SceneManager::Get().ChangeScene("Outgame");
             });
         });

     ObjFactory::Get().RegisterObject("인게임_2", []() {
         int x = 147;
         int y = 570;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 64 },
             [](const MSG& msg) {
                 cout << "창고" << endl;
                 //SceneManager::Get().ChangeScene("Ingame");
             });
         });

     ObjFactory::Get().RegisterObject("인게임_3", []() {
         int x = 147;
         int y = 703;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 64 },
             [](const MSG& msg) {
                 cout << "장비" << endl;
                 //SceneManager::Get().ChangeScene("Ingame");
             });
         });

     ObjFactory::Get().RegisterObject("인게임_4", []() {
         int x = 147;
         int y = 836;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 64 },
             [](const MSG& msg) {
                 cout << "스테이터스" << endl;
                 //SceneManager::Get().ChangeScene("Ingame");
             });
         });


     ObjFactory::Get().RegisterObject("Player", []() {
         return std::make_unique<Player>(
             RECT{ 600, 300, 1000, 500 }
         );
         });



     /*
     * 나는 노가다 잘함
     * 
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
        */
}






