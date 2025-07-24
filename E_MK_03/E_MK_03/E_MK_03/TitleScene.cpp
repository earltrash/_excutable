#include "pch.h"
#include "TitleScene.h"
#include "Button.h"
#include "SceneManager.h"

void TitleScene::Initalize() //ui ������Ʈ, �����ϴ� ������ ũ���� �迭�� �� ��. 
{
	std::cout << "Title �����̾�" << std::endl;
	
	
	GetAsset(SceneIndex);
	UISet();
	AssetMapping();
}




void TitleScene::Enter()//��� �ʿ���� ����?
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
		RECT{ 600, 300, 1000, 500 }, // ������ png�� ���߱� �ϴµ�,  

		[](const MSG& msg) { SceneManager::Get().ChangeScene(Stage); }
	));



	/*m_gameObjects.emplace("Exit", std::make_unique<Button>(
		RECT{ 600, 450, 1000, 650 },
		[](const MSG& msg) { PostQuitMessage(0); }
	));*/

	return (m_gameObjects.size() == 0); //�ϰ͵� ���ٸ�� 
}


bool TitleScene::AssetMapping()
{
	for (auto& [name, obj] : m_gameObjects) { //map�� auto �ݺ����� �̷� ����...
		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) { //���� ������Ʈ�� �̸��� clip_Asset�� Name�� ���� ��� (json parssing)
				obj->AddClip(asset.Ani_Name, asset.clip); //�� ������Ʈ�� ���� clip���� �־���. 

				if (asset.Ani_Name == "Idle") //�ϴ� �ӽ÷� �̷��� ��. 
					obj->SetCurrentClip(asset.clip); 
			}
		}
	}

	for (const auto& [name, obj] : m_gameObjects) //���õ� ������ CLIP �ּҸ� SPRITEANIMATOR�� �־� ��. & CURSPRITE���ٰ���, 
	{
		SpriteAnimator ap;
		ap.SetClip(&obj->GetCurrentClip()); //
		m_curSprites.emplace(obj.get() , ap); //�׷��� VECTOR�� �����ϴ� �Ű� 
	}
	return false;
}
