#pragma once
#include "pch.h"
#include "Factory.h"
#include "Button.h"
#include "Player.h"
#include "SceneManager.h"


//Engine�� �ִ� factory�� ������ ������ �Ѱ��� 
void ObjectRegister() //���ӿ� ���� ��� obj �����ڸ� ��Ͻ�Ŵ 
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