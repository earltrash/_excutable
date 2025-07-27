#pragma once
#include "pch.h"
#include "Scene.h"
#include "ObjFactory.h"

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

	void SceneRegister() //일단 예시, 초기화 값이 좀 무거워 질 수도 있을 거 같다는 생각이 들긴 함. ㅇㅇ 
	{
		if (!ObjFactory::Get().m_objectCreators.empty()) //사전에 ObjectFactory에 값이 있어야 함

			m_sceneInitializers.emplace("Title", [](SceneStandard& scene)
				{

			auto obj = ObjFactory::Get().CreateObject("Start");
			scene.m_gameObjects.emplace("Start", std::move(obj));

			obj = ObjFactory::Get().CreateObject("Exit");
			scene.m_gameObjects.emplace("Exit", std::move(obj));

				});




		m_sceneInitializers.emplace("Stage", [](SceneStandard& scene) {
			auto obj = ObjFactory::Get().CreateObject("Player");
			scene.m_gameObjects.emplace("Player", std::move(obj));
			});

	}




public:
	std::map<string, SceneInitFunction> m_sceneInitializers; //Scene Init에 필요한 함수를 보관 key로 받음


};