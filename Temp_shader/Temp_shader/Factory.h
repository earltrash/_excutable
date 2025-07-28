#pragma once
#include "pch.h"
#include "ObjFactory.h"
#include "Button.h"
#include "Player.h"
#include "SceneManager.h"


//Engine에 있는 factory에 생성자 정보만 넘겨줌 
//게임에 사용될 모든 obj 생성자를 등록시킴 - SceneFactory에서 string으로 mapping 


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