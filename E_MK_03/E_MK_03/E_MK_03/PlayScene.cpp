#include "pch.h"
#include "PlayScene.h"
#include "Player.h"

void PlayScene::Initalize() //게임오브젝트 관리하는 오브젝트를 여기에 담아야 함. 
{
	//게임 오브젝트 생성
	GetAsset(SceneIndex);
	assert(!SceneAssets.empty());

	PlayerSet();
	

	for (auto& [name, obj] : m_gameObjects) { //map의 auto 반복문은 이런 구조...
		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) {
				obj->AddClip(asset.Ani_Name, asset.clip);
				if (asset.Ani_Name == "Idle") //일단 임시로 이렇게 씀. 
					obj->SetCurrentClip(asset.clip);
				//기본값은 idle 혹은 default라는 고정 컨벤션을 통해서 설정함. 
			}
		}
	}

	for (const auto& [name, obj] : m_gameObjects) //선택된 파일의 CLIP 주소를 SPRITEANIMATOR에 넣어 줌. & CURSPRITE에다가도, AUTO가 진짜 좋은 게, 
	{
		SpriteAnimator ap;

		ap.SetClip(&obj->GetCurrentClip()); //CLIPS에 있는 CLIP 넣어주기, CLIP 갯수만큼 반복 되겠죠?
		m_curSprites.emplace(obj.get(), ap); //그래서 VECTOR로 관리하는 거고 
	}

}





void PlayScene::Enter()
{
	Initalize();
}

void PlayScene::Exit()
{
	Clean();
}

void PlayScene::PlayerSet()
{
	m_gameObjects.emplace("Player",
		std::make_unique<Player>(RECT{600, 100, 800, 200})); //매개변수는 딱히 필요 없고. 생성자에서 처리하려고 함.

	//비트맵 잘 나감요 
	//m_gameObjects.emplace("Player",
	//	std::make_unique<Player>(RECT{ 1200, 100, 1400, 200 })); //매개변수는 딱히 필요 없고. 생성자에서 처리하려고 함.
}

void PlayScene::EnemyInstantitate()
{

}
