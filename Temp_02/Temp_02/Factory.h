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