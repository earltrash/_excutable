#include "pch.h"
#include "TitleScene.h"
#include "Button.h"
#include "SceneManager.h"



void TitleScene::Enter()//얘는 필요없긴 하지?
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
		RECT{ 600, 300, 1000, 500 }, // 범위는 png랑 맞추긴 하는데,  

		[](const MSG& msg) { SceneManager::Get().ChangeScene(Stage); }
	));




	return m_gameObjects.empty();
}



