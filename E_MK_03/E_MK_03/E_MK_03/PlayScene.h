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
	//타이머를 참조로 받거나 singleton으로 받는 애가 필요할 거 같아 
};