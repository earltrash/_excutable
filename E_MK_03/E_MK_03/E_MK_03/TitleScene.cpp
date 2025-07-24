#include "pch.h"
#include "TitleScene.h"
#include "Button.h"
#include "SceneManager.h"



void TitleScene::Enter()//��� �ʿ���� ����?
{
	Initalize();
}

void TitleScene::Exit()
{
	Clean();
}



bool TitleScene::ObjCreate()
{
	m_gameObjects.emplace("Start", std::make_unique<Button>(
		RECT{ 600, 300, 1000, 500 }, // ������ png�� ���߱� �ϴµ�,  

		[](const MSG& msg) { SceneManager::Get().ChangeScene(Stage); }
	));




	return m_gameObjects.empty();
}



