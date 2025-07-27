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
			it->second(scene);  // ���⼭ ���� ����
		else
			std::cerr << "SceneInit key not found: " << key << "\n";
	}

	void SceneRegister() //�ϴ� ����, �ʱ�ȭ ���� �� ���ſ� �� ���� ���� �� ���ٴ� ������ ��� ��. ���� 
	{
		if (!ObjFactory::Get().m_objectCreators.empty()) //������ ObjectFactory�� ���� �־�� ��

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
	std::map<string, SceneInitFunction> m_sceneInitializers; //Scene Init�� �ʿ��� �Լ��� ���� key�� ����


};