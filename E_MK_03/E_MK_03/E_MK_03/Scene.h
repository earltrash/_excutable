#pragma once
#include "pch.h"
#include "IAssetProvider.h"
#include "AnimationClip.h"
#include "Object.h"
#include "Camera2D.h"

class SceneFactory;

using Provider = std::shared_ptr<IAssetProvider>;
using Renderer = std::shared_ptr<D2DRenderer>;


class SceneStandard 
{
	friend class SceneFactory;

public: //다 열어주는 거 맘에 안 들긴 하는데, core랑 manager에서 쓸려면 어쩔 수 없는듯.

	SceneStandard(string name, Provider provider, Renderer renderer); //이름이랑 Provider Renderer만 있으면 되니깐 
	~SceneStandard() = default;
 
	virtual void Initalize(); //SpriteAnimator 를 여기서 만들어도 되지 않을까. 만들어지는 시점은 
	virtual void Clean();
	//위 둘을 인터페이스로 넣는거는 취향 영역인듯함. 

	virtual void Update();
	virtual void LogicUpdate(float delta);
	virtual void Enter() { Initalize(); };

	virtual void Exit() { Clean(); }; //하위 클래스에서 처리 
	virtual void Render();


protected:
	void SetAssetProvider(Provider AssetProvider) { m_assetProvider = AssetProvider;}
	void SetRenderer(const Renderer& renderer) { m_renderer = renderer; }
	void GetAsset(string info) { SceneAssets = m_assetProvider->GetClips(info);}
	void AssetMapping();

	virtual bool ObjCreate() { return true; };
protected:
	Provider m_assetProvider ; //자식은 쓰게 해주자. 굳이 Get으로 넘겨줄 이유는 못 찾겠음.
	Renderer m_renderer ;

	std::vector<Clip_Asset> SceneAssets;
	std::multimap<std::string, std::unique_ptr<Object>> m_gameObjects; //이번Scene에 사용되는 게임 obj


	bool dirty = false;
	string m_name;

};


