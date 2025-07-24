#pragma once
#include "Scene.h"
#include "Sceneinfo.h"



class PlayScene : public  SceneStandard {

public:
	PlayScene(SceneInfo index, Provider AssetProvider, const Renderer& renderer)
	{
		SetAssetProvider(AssetProvider);
		SetRenderer(renderer);
		SetSceneInfo(index);
	};
	~PlayScene() = default;
private:

	//void Initalize() override;
	void Enter() override;
	void Exit() override;

	bool ObjCreate() override;
};