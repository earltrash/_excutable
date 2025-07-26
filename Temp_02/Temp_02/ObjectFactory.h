#pragma once
#include "pch.h"
#include "Factory.h"
#include "Button.h"
#include "Player.h"
#include "SceneManager.h"


//Engine에 있는 factory에 생성자 정보만 넘겨줌 
void ObjectRegister() //게임에 사용될 모든 obj 생성자를 등록시킴 
{
    ObjFactory::Get().RegisterObject("Start", []() {
        return std::make_unique<Button>(
            RECT{ 600, 300, 1000, 500 },
            [](const MSG& msg) {
                SceneManager::Get().ChangeScene("Stage");
            });
        });


    ObjFactory::Get().RegisterObject("Player", []() {
        return std::make_unique<Player>(
            RECT{ 600, 300, 1000, 500 }
        );
        });
        

}