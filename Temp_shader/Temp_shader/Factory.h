#pragma once
#include "pch.h"
#include "ObjFactory.h"
#include "Button.h"
#include "Player.h"
#include "SceneManager.h"


//Engine�� �ִ� factory�� ������ ������ �Ѱ��� 
//���ӿ� ���� ��� obj �����ڸ� ��Ͻ�Ŵ - SceneFactory���� string���� mapping 


void ObjectRegister() 
{
    ObjFactory::Get().RegisterObject("temp_0001", []() 
        {
        auto temp_0001 =
         std::make_unique<Button>(
            RECT{ 0 , 0, 1000000   , 600 },
            [](const MSG& msg) {
            });
        return temp_0001;
        }
    );


    //ObjFactory::Get().RegisterObject("Start", []()
    //    {
    //        auto startButton =
    //            std::make_unique<Button>(
    //                RECT{ 600, 300, 1000, 500 },
    //                [](const MSG& msg) {
    //                    SceneManager::Get().ChangeScene("Stage");
    //                });
    //        startButton->SetEnabled(false);
    //        return startButton;
    //    }
    //);


    ObjFactory::Get().RegisterObject("Exit", []() {
        return std::make_unique<Button>(
            RECT{ 600, 600, 1000, 800 },
            [](const MSG& msg) {
                PostQuitMessage(0);
            });
        });

}