#pragma once
#include "Scene.h"
#include "Sceneinfo.h"



class EndScene : public  SceneStandard {

public:
	EndScene(SceneInfo index, Provider AssetProvider, const Renderer& renderer) : SceneIndex(index)
	{
		SetAssetProvider(AssetProvider);
		SetRenderer(renderer);
	};


	~EndScene() = default;
private:
	void Initalize() override;
	void Clean()  override;
	void Enter() override;
	void Exit() override;
private:
	SceneInfo SceneIndex;
};