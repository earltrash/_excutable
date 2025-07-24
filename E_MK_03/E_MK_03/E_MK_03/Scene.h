#pragma once
#include "pch.h"
#include "IScene.h"
#include "IAssetProvider.h"
#include "Sceneinfo.h"
#include "AnimationClip.h"
#include "Object.h"
#include "Camera2D.h"

using Provider = std::shared_ptr<IAssetProvider>;
using Renderer = std::shared_ptr<D2DRenderer>;


class SceneStandard : IScene
{
public: //�� �����ִ� �� ���� �� ��� �ϴµ�, core�� manager���� ������ ��¿ �� ���µ�.

	SceneStandard() = default;; //���� ��, �� �ε��� �ް� ����.
	~SceneStandard() = default;
 
	virtual void Initalize(); //SpriteAnimator �� ���⼭ ���� ���� ������. ��������� ������ 
	virtual void Clean();
	//�� ���� �������̽��� �ִ°Ŵ� ���� �����ε���. 

	virtual void Update();
	virtual void LogicUpdate(float delta);
	virtual void Enter(){};
	virtual void Exit() { Clean(); }; //���� Ŭ�������� ó�� 
	virtual void Render();


protected:
	void SetAssetProvider(Provider AssetProvider) { m_assetProvider = AssetProvider;}
	void SetRenderer(const Renderer& renderer) { m_renderer = renderer; }
	void GetAsset(SceneInfo info) { SceneAssets = m_assetProvider->GetClips(info);}

protected:
	Provider m_assetProvider ; //�ڽ��� ���� ������. ���� Get���� �Ѱ��� ������ �� ã����.
	Renderer m_renderer ;

	std::vector<Clip_Asset> SceneAssets;
	std::multimap<std::string, std::unique_ptr<Object>> m_gameObjects; //�̹�Scene�� ���Ǵ� ���� obj
	std::unordered_map<Object* ,SpriteAnimator>  m_curSprites;


	bool dirty = false;
};


