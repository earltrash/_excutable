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

public: //�� �����ִ� �� ���� �� ��� �ϴµ�, core�� manager���� ������ ��¿ �� ���µ�.

	SceneStandard(string name, Provider provider, Renderer renderer); //�̸��̶� Provider Renderer�� ������ �Ǵϱ� 
	~SceneStandard() = default;
 
	virtual void Initalize(); //SpriteAnimator �� ���⼭ ���� ���� ������. ��������� ������ 
	virtual void Clean();
	//�� ���� �������̽��� �ִ°Ŵ� ���� �����ε���. 

	virtual void Update();
	virtual void LogicUpdate(float delta);
	virtual void Enter() { Initalize(); };

	virtual void Exit() { Clean(); }; //���� Ŭ�������� ó�� 
	virtual void Render();


protected:
	void SetAssetProvider(Provider AssetProvider) { m_assetProvider = AssetProvider;}
	void SetRenderer(const Renderer& renderer) { m_renderer = renderer; }
	void GetAsset(string info) { SceneAssets = m_assetProvider->GetClips(info);}
	void AssetMapping();

	virtual bool ObjCreate() { return true; };
protected:
	Provider m_assetProvider ; //�ڽ��� ���� ������. ���� Get���� �Ѱ��� ������ �� ã����.
	Renderer m_renderer ;

	std::vector<Clip_Asset> SceneAssets;
	std::multimap<std::string, std::unique_ptr<Object>> m_gameObjects; //�̹�Scene�� ���Ǵ� ���� obj


	bool dirty = false;
	string m_name;

};


