#include "pch.h"
#include "TitleScene.h"
#include "Button.h"
#include "SceneManager.h"

void TitleScene::Initalize() //ui 오브젝트, 관리하는 고정적 크기의 배열을 쓸 듯. 
{
	std::cout << "Title 시작이야" << std::endl;
	
	
	GetAsset(SceneIndex);
	UISet();
	AssetMapping();
}




void TitleScene::Enter()//얘는 필요없긴 하지?
{
	Initalize();
}

void TitleScene::Exit()
{
	Clean();
}

bool TitleScene::UISet()
{
	m_gameObjects.emplace("Start", std::make_unique<Button>(
		RECT{ 600, 300, 1000, 500 }, // 범위는 png랑 맞추긴 하는데,  

		[](const MSG& msg) { SceneManager::Get().ChangeScene(Stage); }
	));



	/*m_gameObjects.emplace("Exit", std::make_unique<Button>(
		RECT{ 600, 450, 1000, 650 },
		[](const MSG& msg) { PostQuitMessage(0); }
	));*/

	return (m_gameObjects.size() == 0); //암것도 없다면야 
}


bool TitleScene::AssetMapping()
{
	for (auto& [name, obj] : m_gameObjects) { //map의 auto 반복문은 이런 구조...
		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) { //게임 오브젝트의 이름과 clip_Asset의 Name과 같은 경우 (json parssing)
				obj->AddClip(asset.Ani_Name, asset.clip); //한 오브젝트의 여러 clip들을 넣어줌. 

				if (asset.Ani_Name == "Idle") //일단 임시로 이렇게 씀. 
					obj->SetCurrentClip(asset.clip); 
			}
		}
	}

	for (const auto& [name, obj] : m_gameObjects) //선택된 파일의 CLIP 주소를 SPRITEANIMATOR에 넣어 줌. & CURSPRITE에다가도, 
	{
		SpriteAnimator ap;
		ap.SetClip(&obj->GetCurrentClip()); //
		m_curSprites.emplace(obj.get() , ap); //그래서 VECTOR로 관리하는 거고 
	}
	return false;
}
