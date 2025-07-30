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

			auto 
			obj = ObjFactory::Get().CreateObject("시작화면_0");
			         scene.m_gameObjects.emplace("시작화면_0", std::move(obj));
			obj = ObjFactory::Get().CreateObject("시작화면_1");
			         scene.m_gameObjects.emplace("시작화면_1", std::move(obj));
			obj = ObjFactory::Get().CreateObject("시작화면_2");
					 scene.m_gameObjects.emplace("시작화면_2", std::move(obj));
			obj = ObjFactory::Get().CreateObject("시작화면_3");
					 scene.m_gameObjects.emplace("시작화면_3", std::move(obj));
			obj = ObjFactory::Get().CreateObject("시작화면_4");
					 scene.m_gameObjects.emplace("시작화면_4", std::move(obj));
					//기존 방식이랑 다르게, Object에 있는 

					//2개는 못 만드니. 해당 오브젝트의 소유권에 대해서 고민 해봐야 할 듯 

					/*auto obj = ObjFactory::Get().CreateObject("Steel Armor");
					scene.m_gameObjects.emplace("Steel Armor", std::move(obj));*/

					
				});

		m_sceneInitializers.emplace("Outgame", [](SceneStandard& scene) {
			auto 
				obj = ObjFactory::Get().CreateObject("시작화면_0");
			scene.m_gameObjects.emplace("시작화면_0", std::move(obj));
				obj = ObjFactory::Get().CreateObject("아웃게임_1");
				         scene.m_gameObjects.emplace("아웃게임_1", std::move(obj));
				obj = ObjFactory::Get().CreateObject("아웃게임_2");
				         scene.m_gameObjects.emplace("아웃게임_2", std::move(obj));
				obj = ObjFactory::Get().CreateObject("아웃게임_3");
				         scene.m_gameObjects.emplace("아웃게임_3", std::move(obj));
				obj = ObjFactory::Get().CreateObject("아웃게임_4");
				         scene.m_gameObjects.emplace("아웃게임_4", std::move(obj));
				obj = ObjFactory::Get().CreateObject("아웃게임_5");
				         scene.m_gameObjects.emplace("아웃게임_5", std::move(obj));
			});


		m_sceneInitializers.emplace("Ingame", [](SceneStandard& scene) {
			auto 
				obj = ObjFactory::Get().CreateObject("시작화면_0");
			scene.m_gameObjects.emplace("시작화면_0", std::move(obj));
				obj = ObjFactory::Get().CreateObject("인게임_1");
				         scene.m_gameObjects.emplace("인게임_1", std::move(obj));
				obj = ObjFactory::Get().CreateObject("인게임_2");
				         scene.m_gameObjects.emplace("인게임_2", std::move(obj));
				obj = ObjFactory::Get().CreateObject("인게임_3");
				         scene.m_gameObjects.emplace("인게임_3", std::move(obj));
				obj = ObjFactory::Get().CreateObject("인게임_4");
				         scene.m_gameObjects.emplace("인게임_4", std::move(obj));

			});


		m_sceneInitializers.emplace("End", [](SceneStandard& scene) {
			auto
				obj = ObjFactory::Get().CreateObject("시작화면_0");
			scene.m_gameObjects.emplace("시작화면_0", std::move(obj));
			
			});

		//m_sceneInitializers.emplace("Outgame", [](SceneStandard& scene) {
		//	auto obj = ObjFactory::Get().CreateObject("Player");
		//	scene.m_gameObjects.emplace("Player", std::move(obj));
		//	});

	}




public:
	std::map<string, SceneInitFunction> m_sceneInitializers; //Scene Init에 필요한 함수를 보관 key로 받음


};