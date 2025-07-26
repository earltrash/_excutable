#pragma once
#include "pch.h"
#include "Scene.h"
#include "Factory.h"

using SceneInitFunction = std::function<void(SceneStandard&)>;
using Function = std::function<void()>;
using namespace std;

class SceneFactory {

private:
	SceneFactory() = default;
	~SceneFactory() = default;



public:
	static SceneFactory& Get()
	{
		static SceneFactory SceneInit;
		return SceneInit;
	}

	void InitScene(const std::string& key, SceneStandard& scene)
	{
		auto it = m_sceneInitializers.find(key);
		if (it != m_sceneInitializers.end())
			it->second(scene);  // 여기서 접근 가능
		else
			std::cerr << "SceneInit key not found: " << key << "\n";
	}

	void SceneRegister() //일단 예시 
	{
		if (!ObjFactory::Get().m_objectCreators.empty())

			m_sceneInitializers.emplace("Title", [](SceneStandard& scene) {
			auto obj = ObjFactory::Get().CreateObject("Start");
			scene.m_gameObjects.emplace("Start", std::move(obj));
				});


		m_sceneInitializers.emplace("Stage", [](SceneStandard& scene) {
			auto obj = ObjFactory::Get().CreateObject("Player");
			scene.m_gameObjects.emplace("Player", std::move(obj));
			});



	}




public:
	std::map<string, SceneInitFunction> m_sceneInitializers;


};