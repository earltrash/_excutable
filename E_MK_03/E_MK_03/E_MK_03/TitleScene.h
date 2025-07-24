#pragma once
#include "Scene.h"
#include "Sceneinfo.h"

class TitleScene : public  SceneStandard {

//using Provider = std::shared_ptr<IAssetProvider>;

public:
	TitleScene(SceneInfo index, Provider AssetProvider, const Renderer& renderer) : SceneIndex(index)
	{
		SetAssetProvider(AssetProvider); 
		SetRenderer(renderer);
	}; 

	~TitleScene() = default;
private:

	void Initalize() override;
	//void Clean()  override ;
	void Enter() override;
	void Exit() override;

	bool UISet();
	bool AssetMapping();


private:
	SceneInfo SceneIndex; 
};