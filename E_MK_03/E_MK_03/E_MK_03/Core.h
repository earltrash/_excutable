#pragma once
#include "pch.h"
#include "WinD.h"
#include "Scene.h"
#include "Timer.h"
#include "Dispatcher.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Camera2D.h"
//#include "AssetProvider.h"

using Microsoft::WRL::ComPtr;
using namespace std;

class AssetProvider;

class M_Core : public WinD
{
	
public:

	M_Core() = default;
	virtual ~M_Core() = default;
	/// <summary> PreInit



	void Init();
	bool ComInit();
	bool ModuleInit(); // ��� ��ü �ν��Ͻ� ������ & �ʱ�ȭ �� �Ҵ� ; InputManager
	/// <summary> Init level : �ʱ�ȭ �� ����
	/// <summary> Init level : �ʱ�ȭ �� ����
	

	void GameLoop();
#pragma region Loop
	void Run();
	void FixedUpdate();
	void Update();
	void Render();
#pragma endregion
	/// </summary> Run level  : loop 
	/// </summary> Run level  : loop 


	void End();
	/// </summary> Run level : Clean
	/// </summary> Run level : Clean
	void ModuleClean();

private:
	int width;
	int height;


	std::unique_ptr<GameTimer> m_timer = nullptr; //timer�� app������ �ʿ��ϴ�, �̱�������� �ʿ� ����.
	std::unique_ptr<EventDispatcher> m_tmp_broadcaster = nullptr; 
	std::shared_ptr<unordered_map<string, shared_ptr<SceneStandard> > > m_Scene_map = nullptr;
	std::shared_ptr<D2DRenderer> m_Renderer = nullptr;
	std::shared_ptr<ResourceManager> m_resourceManager = nullptr;

};