#pragma once
#include "pch.h"
#include "WinD.h"
#include "Scene.h"
#include "Timer.h"
#include "Dispatcher.h"
#include "Dummy.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Camera2D.h"

using Microsoft::WRL::ComPtr;
using namespace std;


class M_Core : public WinD
{
	
public:

	M_Core() = default;
	virtual ~M_Core() = default;
	/// <summary> PreInit



	void Init();
	bool ComInit();
	bool ModuleInit(); // 모듈 객체 인스턴스 가져옴 & 초기화 및 할당 ; InputManager
	// 싱글톤 및 객체들 전달해주거나 처리하는 과정도 필요 
	/// <summary> Init level : 초기화 및 생성
	/// <summary> Init level : 초기화 및 생성
	

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
	std::unique_ptr<GameTimer> m_timer = nullptr; //timer는 app에서만 필요하니, 싱글톤까지는 필요 없음.
	std::unique_ptr<EventDispatcher> m_tmp_broadcaster = nullptr; 
	std::unique_ptr<Dummy> m_Dummy = nullptr;
	std::shared_ptr<unordered_map<SceneInfo, shared_ptr<SceneStandard> > > m_Scene_map = nullptr;
	std::shared_ptr<D2DRenderer> m_Renderer = nullptr;
	std::shared_ptr<ResourceManager> m_resourceManager = nullptr;

};