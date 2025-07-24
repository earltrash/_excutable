#include "pch.h"
#include "PlayScene.h"
#include "Player.h"






void PlayScene::Enter()
{
	Initalize();
}

void PlayScene::Exit()
{
	Clean();
}


bool PlayScene::ObjCreate()
{
	m_gameObjects.emplace("Player",
		std::make_unique<Player>(RECT{ 600, 100, 800, 200 })); 



	return m_gameObjects.empty(); 
}


