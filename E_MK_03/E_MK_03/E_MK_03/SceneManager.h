#pragma once
#include "pch.h"

#include "TitleScene.h"
#include "PlayScene.h"
#include "EndScene.h"



#include "Scene.h"
#include "IScene.h"
#include "AssetProvider.h"

using namespace std;

class SceneManager {
private:
	SceneManager() = default; 
	~SceneManager() = default;
public:

	void Initalize(shared_ptr<unordered_map<SceneInfo, shared_ptr<SceneStandard>>> & Scenes) //자료구조는 깔끔한데, 확장성은 떨어지는 거 같아...
	{
		//이건 좀 줄여야 할 듯. 
		Scenes->emplace(SceneInfo::Title, make_shared<TitleScene>((SceneInfo::Title), m_assetProvider, m_Renderer));
		Scenes->emplace(SceneInfo::Stage, make_shared<PlayScene>((SceneInfo::Stage), m_assetProvider, m_Renderer));
		Scenes->emplace(SceneInfo::End, make_shared<EndScene>((SceneInfo::End), m_assetProvider, m_Renderer));

		std::cout << "use count" << m_Renderer.use_count() << std::endl;

		//최초 Scene은 Title값 -> 
		m_currentindex = Title;
		Scene_map = make_shared<unordered_map<SceneInfo, shared_ptr<SceneStandard>>>();
		Scene_map = Scenes;
		Scene_map->at(static_cast<SceneInfo>(m_currentindex))->Enter(); //다음은 바로 update니깐 

	}


	//그럼 얘는 core랑 얘기 되어야 할듯? 

	void ChangeScene(SceneInfo index) { 
		InputManager::Get().IgnoreNextInput();

		MSG msg;
		while (PeekMessage(&msg, nullptr, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE)) {}


		Scene_map->at(static_cast<SceneInfo>(m_currentindex))->Exit();
		m_currentindex = index;
		Scene_map->at(static_cast<SceneInfo>(m_currentindex))->Enter();
	};

	static SceneManager& Get() {
		static SceneManager scenemanager;
		return scenemanager;
	};

	int GetCurrentIndex() //이게 최저 수준의 소통 수준 
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

		for (auto& [key, scene] : *Scene_map)
		{
			scene->Clean();
		}
	}


public:
	SceneInfo m_currentindex;
	shared_ptr<unordered_map<SceneInfo, shared_ptr<SceneStandard>>> Scene_map = nullptr; //core의 Scene이랑 공유함.
	std::shared_ptr<IAssetProvider> m_assetProvider;
	std::shared_ptr<D2DRenderer> m_Renderer;
};
