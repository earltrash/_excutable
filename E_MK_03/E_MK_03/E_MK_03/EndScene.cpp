#include "pch.h"
#include "EndScene.h"


void EndScene::Enter()
{
    Initalize();
}

void EndScene::Exit()
{
    Clean();
}

bool EndScene::ObjCreate()
{


    return m_gameObjects.empty();
}
