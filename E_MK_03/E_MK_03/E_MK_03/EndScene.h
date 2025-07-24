#pragma once
#include "Scene.h"
#include "Sceneinfo.h"



class EndScene : public  SceneStandard {

public:
	EndScene(SceneInfo index, Provider AssetProvider, const Renderer& renderer)
	{
		SetAssetProvider(AssetProvider);
		SetRenderer(renderer);
		SetSceneInfo(index);
	};


	~EndScene() = default;
private:
	void Enter() override;
	void Exit() override;

	bool ObjCreate() override;

};