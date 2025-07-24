#include "pch.h"
#include "PlayScene.h"
#include "Player.h"

void PlayScene::Initalize() //���ӿ�����Ʈ �����ϴ� ������Ʈ�� ���⿡ ��ƾ� ��. 
{
	//���� ������Ʈ ����
	GetAsset(SceneIndex);
	assert(!SceneAssets.empty());

	PlayerSet();
	

	for (auto& [name, obj] : m_gameObjects) { //map�� auto �ݺ����� �̷� ����...
		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) {
				obj->AddClip(asset.Ani_Name, asset.clip);
				if (asset.Ani_Name == "Idle") //�ϴ� �ӽ÷� �̷��� ��. 
					obj->SetCurrentClip(asset.clip);
				//�⺻���� idle Ȥ�� default��� ���� �������� ���ؼ� ������. 
			}
		}
	}

	for (const auto& [name, obj] : m_gameObjects) //���õ� ������ CLIP �ּҸ� SPRITEANIMATOR�� �־� ��. & CURSPRITE���ٰ���, AUTO�� ��¥ ���� ��, 
	{
		SpriteAnimator ap;

		ap.SetClip(&obj->GetCurrentClip()); //CLIPS�� �ִ� CLIP �־��ֱ�, CLIP ������ŭ �ݺ� �ǰ���?
		m_curSprites.emplace(obj.get(), ap); //�׷��� VECTOR�� �����ϴ� �Ű� 
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
		std::make_unique<Player>(RECT{600, 100, 800, 200})); //�Ű������� ���� �ʿ� ����. �����ڿ��� ó���Ϸ��� ��.

	//��Ʈ�� �� ������ 
	//m_gameObjects.emplace("Player",
	//	std::make_unique<Player>(RECT{ 1200, 100, 1400, 200 })); //�Ű������� ���� �ʿ� ����. �����ڿ��� ó���Ϸ��� ��.
}

void PlayScene::EnemyInstantitate()
{

}
