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

			auto 
			obj = ObjFactory::Get().CreateObject("����ȭ��_0");
			         scene.m_gameObjects.emplace("����ȭ��_0", std::move(obj));
			obj = ObjFactory::Get().CreateObject("����ȭ��_1");
			         scene.m_gameObjects.emplace("����ȭ��_1", std::move(obj));
			obj = ObjFactory::Get().CreateObject("����ȭ��_2");
					 scene.m_gameObjects.emplace("����ȭ��_2", std::move(obj));
			obj = ObjFactory::Get().CreateObject("����ȭ��_3");
					 scene.m_gameObjects.emplace("����ȭ��_3", std::move(obj));
			obj = ObjFactory::Get().CreateObject("����ȭ��_4");
					 scene.m_gameObjects.emplace("����ȭ��_4", std::move(obj));
					//���� ����̶� �ٸ���, Object�� �ִ� 

					//2���� �� �����. �ش� ������Ʈ�� �����ǿ� ���ؼ� ��� �غ��� �� �� 

					/*auto obj = ObjFactory::Get().CreateObject("Steel Armor");
					scene.m_gameObjects.emplace("Steel Armor", std::move(obj));*/

					
				});

		m_sceneInitializers.emplace("Outgame", [](SceneStandard& scene) {
			auto 
				obj = ObjFactory::Get().CreateObject("����ȭ��_0");
			scene.m_gameObjects.emplace("����ȭ��_0", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ƿ�����_1");
				         scene.m_gameObjects.emplace("�ƿ�����_1", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ƿ�����_2");
				         scene.m_gameObjects.emplace("�ƿ�����_2", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ƿ�����_3");
				         scene.m_gameObjects.emplace("�ƿ�����_3", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ƿ�����_4");
				         scene.m_gameObjects.emplace("�ƿ�����_4", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ƿ�����_5");
				         scene.m_gameObjects.emplace("�ƿ�����_5", std::move(obj));
			});


		m_sceneInitializers.emplace("Ingame", [](SceneStandard& scene) {
			auto 
				obj = ObjFactory::Get().CreateObject("����ȭ��_0");
			scene.m_gameObjects.emplace("����ȭ��_0", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ΰ���_1");
				         scene.m_gameObjects.emplace("�ΰ���_1", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ΰ���_2");
				         scene.m_gameObjects.emplace("�ΰ���_2", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ΰ���_3");
				         scene.m_gameObjects.emplace("�ΰ���_3", std::move(obj));
				obj = ObjFactory::Get().CreateObject("�ΰ���_4");
				         scene.m_gameObjects.emplace("�ΰ���_4", std::move(obj));

			});


		m_sceneInitializers.emplace("End", [](SceneStandard& scene) {
			auto
				obj = ObjFactory::Get().CreateObject("����ȭ��_0");
			scene.m_gameObjects.emplace("����ȭ��_0", std::move(obj));
			
			});

		//m_sceneInitializers.emplace("Outgame", [](SceneStandard& scene) {
		//	auto obj = ObjFactory::Get().CreateObject("Player");
		//	scene.m_gameObjects.emplace("Player", std::move(obj));
		//	});

	}




public:
	std::map<string, SceneInitFunction> m_sceneInitializers; //Scene Init�� �ʿ��� �Լ��� ���� key�� ����


};