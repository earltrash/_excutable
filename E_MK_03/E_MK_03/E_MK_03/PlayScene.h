#pragma once
#include "Scene.h"
#include "Sceneinfo.h"



class PlayScene : public  SceneStandard {

public:
	PlayScene(SceneInfo index, Provider AssetProvider, const Renderer& renderer) : SceneIndex(index)
	{
		SetAssetProvider(AssetProvider);
		SetRenderer(renderer);
	};
	~PlayScene() = default;
private:

	void Initalize() override;
	void Enter() override;
	void Exit() override;

	void PlayerSet();
	void EnemyInstantitate();



private:
	SceneInfo SceneIndex;
	//Ÿ�̸Ӹ� ������ �ްų� singleton���� �޴� �ְ� �ʿ��� �� ���� 
};