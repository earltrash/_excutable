#pragma once
#include "pch.h"
#include "Scene.h"
#include "AssetProvider.h"
#include "Factory.h"
#include "SceneFactory.h"

using namespace std;

class SceneManager {
private:
	SceneManager() = default; 
	~SceneManager() = default;
public:

	void Initalize(shared_ptr<unordered_map<string, shared_ptr<SceneStandard>>> & Scenes) //자료구조는 깔끔한데, 확장성은 떨어지는 거 같아...
	{
	//	SceneStandard(string name, Provider provider, Renderer renderer); //이름이랑 Provider Renderer만 있으면 되니깐 
		
		m_Scene_map = make_shared<unordered_map<string, shared_ptr<SceneStandard>>>();


		m_Scene_map->emplace("Title", make_shared<SceneStandard>("Title", m_assetProvider, m_Renderer));
		m_Scene_map->emplace("Stage", make_shared<SceneStandard>("Stage", m_assetProvider, m_Renderer));
		m_Scene_map->emplace("End", make_shared<SceneStandard>("End", m_assetProvider, m_Renderer));
		//일단 임시로 이렇게 하고, 나중에 사용되는 Scene 만큼 넘겨주면 됨 

		//최초 Scene은 Title값 -> 
		m_currentindex = "Title";

		 Scenes = m_Scene_map;

		m_Scene_map->at(m_currentindex)->Enter(); //다음은 바로 update니깐 

	}


	//그럼 얘는 core랑 얘기 되어야 할듯? 

	void ChangeScene(const string& index) { 
		InputManager::Get().IgnoreNextInput();

		MSG msg;
		while (PeekMessage(&msg, nullptr, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE)) {}


		m_Scene_map->at(m_currentindex)->Exit();
		m_currentindex = index;
		m_Scene_map->at(m_currentindex)->Enter();
	};

	static SceneManager& Get() {
		static SceneManager scenemanager;
		return scenemanager;
	};

	string GetCurrentIndex() //이게 최저 수준의 소통 수준 
	{
		return m_currentindex;
	}

	void SetAssetProvider(std::shared_ptr<IAssetProvider> provider) {
		m_assetProvider = provider;
	}
	void SetRenderer(const std::shared_ptr<D2DRenderer>& renderer)
	{
		if (!renderer)
			std::cout << "SetRenderer 전달받은 renderer가 null임!" << std::endl;
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
	shared_ptr<unordered_map<string, shared_ptr<SceneStandard>>> m_Scene_map = nullptr; //core의 Scene이랑 공유함.

	std::shared_ptr<IAssetProvider> m_assetProvider;
	std::shared_ptr<D2DRenderer> m_Renderer;
};
