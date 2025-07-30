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
        std::cout << "���� ���: " << std::filesystem::current_path() << std::endl;

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
            //������� ����� �� ���� �ְڴµ�, ��������� ������ Ÿ���� ������.
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
     LoadItemsFromJson("../OBJ_Json/item.json"); //�ش� ����� json�� �о ������ ���� �Ľ� �� ����


//////////////////////////////
// ����ȭ�� - TitleScen
     ObjFactory::Get().RegisterObject("����ȭ��_0", []() {
         // ��ư -> bg
         return std::make_unique<Button>(
             RECT{ 0, 0, 1920,  1080},
             [](const MSG& msg) {
                 //cout << "background" << endl;
             });
         });


     ObjFactory::Get().RegisterObject("����ȭ��_1", []() {
          // ��ư -> bg
         return std::make_unique<Button>(
             RECT{ 147, 254, 147 + 702,  254 + 83 },
             [](const MSG& msg) {
                 cout << "��Ŭ���� �� �����丮" << endl;
             });
         });


     ObjFactory::Get().RegisterObject("����ȭ��_2", []() {
         int x = 147;
         int y = 564;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 75},
             [](const MSG& msg) {
                 cout << "���� �����մϴ�." << endl;
                 SceneManager::Get().ChangeScene("Outgame");
             });
         });


     ObjFactory::Get().RegisterObject("����ȭ��_3", []() {
         int x = 147;
         int y = 697;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 75 },
             [](const MSG& msg) {
                 cout << "����â�� ŵ/���ϴ�." << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });


     ObjFactory::Get().RegisterObject("����ȭ��_4", []() {
         int x = 147;
         int y = 830;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 75 },
             [](const MSG& msg) {
                 cout << "ũ����â�� ŵ/���ϴ�." << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });


//////////////////////////////
// �ƿ����� - Outgame
     //ObjFactory::Get().RegisterObject("����ȭ��_0", []() {
     //    // ��ư -> bg
     //    // ��� �ϴ� ȸ���� �װ� ����ȭ���̶� �����ϱ� �߰� ����
     //    return std::make_unique<Button>(
     //        RECT{ 0, 0, 1920,  1080 },
     //        [](const MSG& msg) {
     //        });
     //    });

     
         

     ObjFactory::Get().RegisterObject("�ƿ�����_1", []() {
         int x = 455;
         int y = 772;
         return std::make_unique<Button>(
             RECT{ x, y, x + 1010, y + 207 },
             [](const MSG& msg) {
                 cout << "�ؽ�Ʈ �ڽ�" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });

     ObjFactory::Get().RegisterObject("�ƿ�����_2", []() {
         int x = 503;
         int y = 805;
         return std::make_unique<Button>(
             RECT{ x, y, x + 218, y + 41 },
             [](const MSG& msg) {
                 cout << "��Ŭ���� N�� �̸�" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });
     ObjFactory::Get().RegisterObject("�ƿ�����_3", []() {
         int x = 503;
         int y = 869;
         return std::make_unique<Button>(
             RECT{ x, y, x + 304, y + 59 },
             [](const MSG& msg) {
                 cout << "�ؽ�Ʈ ����" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });
     ObjFactory::Get().RegisterObject("�ƿ�����_4", []() {
         int x = 1087;
         int y = 921;
         return std::make_unique<Button>(
             RECT{ x, y, x + 140, y + 40 },
             [](const MSG& msg) {
                 cout << "�� (���� ��ư)" << endl;
                 SceneManager::Get().ChangeScene("Ingame");
             });
         });
     ObjFactory::Get().RegisterObject("�ƿ�����_5", []() {
         int x = 1280;
         int y = 921;
         return std::make_unique<Button>(
             RECT{ x, y, x + 140, y + 40 },
             [](const MSG& msg) {
                 cout << "�ƴϿ� (���� ��ư)" << endl;
                 //SceneManager::Get().ChangeScene("Stage");
             });
         });

//////////////////////////////
// �ΰ��� - Ingame
     ObjFactory::Get().RegisterObject("�ΰ���_1", []() {
         int x = 64;
         int y = 57;
         return std::make_unique<Button>(
             RECT{ x, y, x + 37, y + 37 },
             [](const MSG& msg) {
                 cout << "�ƿ����� �̵� ��ư" << endl;
                 SceneManager::Get().ChangeScene("Outgame");
             });
         });

     ObjFactory::Get().RegisterObject("�ΰ���_2", []() {
         int x = 147;
         int y = 570;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 64 },
             [](const MSG& msg) {
                 cout << "â��" << endl;
                 //SceneManager::Get().ChangeScene("Ingame");
             });
         });

     ObjFactory::Get().RegisterObject("�ΰ���_3", []() {
         int x = 147;
         int y = 703;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 64 },
             [](const MSG& msg) {
                 cout << "���" << endl;
                 //SceneManager::Get().ChangeScene("Ingame");
             });
         });

     ObjFactory::Get().RegisterObject("�ΰ���_4", []() {
         int x = 147;
         int y = 836;
         return std::make_unique<Button>(
             RECT{ x, y, x + 310, y + 64 },
             [](const MSG& msg) {
                 cout << "�������ͽ�" << endl;
                 //SceneManager::Get().ChangeScene("Ingame");
             });
         });


     ObjFactory::Get().RegisterObject("Player", []() {
         return std::make_unique<Player>(
             RECT{ 600, 300, 1000, 500 }
         );
         });



     /*
     * ���� �밡�� ����
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






