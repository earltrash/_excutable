#pragma once
#include "pch.h"
#include "Scene.h"
#include "AssetProvider.h"
#include "ObjFactory.h"
#include "SceneFactory.h"

using namespace std;

class SceneManager {
private:
	SceneManager() = default; 
	~SceneManager() = default;
public:

	void Initalize(shared_ptr<unordered_map<string, shared_ptr<SceneStandard>>> & Scenes) //�ڷᱸ���� ����ѵ�, Ȯ�强�� �������� �� ����...
	{
		
		m_Scene_map = make_shared<unordered_map<string, shared_ptr<SceneStandard>>>();


		m_Scene_map->emplace("Title", make_shared<SceneStandard>("Title", m_assetProvider, m_Renderer));
		m_Scene_map->emplace("Stage", make_shared<SceneStandard>("Stage", m_assetProvider, m_Renderer));
		m_Scene_map->emplace("End", make_shared<SceneStandard>("End", m_assetProvider, m_Renderer));

		m_currentindex = "Title";

		 Scenes = m_Scene_map;

		m_Scene_map->at(m_currentindex)->Enter(); //������ �ٷ� update�ϱ� 

	}


	//�׷� ��� core�� ��� �Ǿ�� �ҵ�? 

	void ChangeScene(const string& index) { 
		InputManager::Get().IgnoreNextInput();

		MSG msg;
		while (PeekMessage(&msg, nullptr, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE)) {} //������ �ִ� msg �����ϱ� 


		m_Scene_map->at(m_currentindex)->Exit();
		m_currentindex = index;
		m_Scene_map->at(m_currentindex)->Enter();
	};

	static SceneManager& Get() {
		static SceneManager scenemanager;
		return scenemanager;
	};

	string GetCurrentIndex() //�̰� ���� ������ ���� ���� 
	{
		return m_currentindex;
	}

	void SetAssetProvider(std::shared_ptr<IAssetProvider> provider) {
		m_assetProvider = provider;
	}
	void SetRenderer(const std::shared_ptr<D2DRenderer>& renderer)
	{
		if (!renderer)
			std::cout << "SetRenderer ���޹��� renderer�� null��!" << std::endl;
		m_Renderer = renderer;
	}

	void Clean()
	{
		m_Renderer.reset();
		m_assetProvider.reset();

		for (auto& [key, scene] : *m_Scene_map)
		{
			scene->Clean();
		}
	}


public:
	string m_currentindex;
	shared_ptr<unordered_map<string, shared_ptr<SceneStandard>>> m_Scene_map = nullptr; //core�� Scene�̶� ������.

	std::shared_ptr<IAssetProvider> m_assetProvider;
	std::shared_ptr<D2DRenderer> m_Renderer;
};
