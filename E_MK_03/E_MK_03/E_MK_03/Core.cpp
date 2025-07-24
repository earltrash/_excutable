#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "Dispatcher.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "IAssetProvider.h"
#include "Sceneinfo.h"

using namespace std;


void M_Core::Init()
{
    const wchar_t* className = L"MK_00";
    const wchar_t* windowName = L"Do_Flight";

    HRESULT hr = __super::Create(className, windowName, 1600, 800); 
    assert(SUCCEEDED(hr));

    hr = ComInit(); // Com 객체 생성 
    assert(SUCCEEDED(hr));

    hr = ModuleInit();     // 매니저의 초기화를 이 단계에서 실행 : 리소스 load & 모듈 멤버 초기화 및 생성
    assert(SUCCEEDED(hr));

    //etc

    std::cout << "Init 성공적" << std::endl; 
   
}


void M_Core::Run() //연구 결과, 프로시저에 InputManager를 넣을 필요는 없음. + 프로시저의 생성 양식은 정해져 있어서 MSG 구조체 전체를 보내줄 수 없기에 여기서 Input 처리
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //특정 메시지만 처리해야 함. 
        {
            if (!InputManager::Get().MsgCheck(msg)) //Inputmanager에서 처리하는 애면 얘가 함, 인풋처리는 여기서 함. 
            {
                TranslateMessage(&msg); //나머지는 프로시저가...
                DispatchMessage(&msg);
            }            
        }
        else 
        {
            m_timer->Tick();
            GameLoop();
        }
    }
}




void M_Core::GameLoop() //event state function render 
{
    FixedUpdate(); //물리 및 판단처리 
    Update();  // event state
    Render(); //렌더
}


void M_Core::FixedUpdate() //시간 처리 
{
    m_Scene_map->at(static_cast<SceneInfo>(SceneManager::Get().GetCurrentIndex()))->LogicUpdate(m_timer->DeltaTime());
}

void M_Core::Update()
{
    m_Scene_map->at(static_cast<SceneInfo>(SceneManager::Get().GetCurrentIndex()))->Update();

}

void M_Core::Render()
{
    m_Scene_map->at(static_cast<SceneInfo>(SceneManager::Get().GetCurrentIndex()))->Render();

}

void M_Core::End()
{
    ModuleClean();
    
}

void M_Core::ModuleClean()
{

    SceneManager::Get().Clean();
    InputManager::Get().Clean();
    m_resourceManager->Clean();
}

bool M_Core::ComInit()  //DX11 기준 
{
    m_Renderer = make_shared<D2DRenderer>();
    m_Renderer->Initialize(m_hWnd);
    ID3D11Device* pd3dDevice = m_Renderer->GetD3DDevice();
    return true;

    
} //일단 보류 

bool M_Core::ModuleInit()
{

    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    std::wcout << L"[exe 위치] " << exePath << std::endl;


    InputManager::Get().m_broadcaster = make_unique<EventDispatcher>(); //이거 디버깅 하나 만들자 
    if (!InputManager::Get().m_broadcaster)
    {
        std::cout << "broadcaster 할당 안됨" << std::endl;
        return false;
    }

    m_resourceManager = make_unique<ResourceManager>();
    //m_resourceManager->AssetLoad(m_Renderer , m_resourceManager->GetAbsoluteResourcePathA() );
     m_resourceManager->AssetLoad(m_Renderer ,"Resource");

    auto provider = std::make_shared<AssetProvider>(m_resourceManager);



    m_Scene_map = make_shared<unordered_map<SceneInfo, shared_ptr<SceneStandard>>>();  //Core가 UPdate로 돌려야 하니
    SceneManager::Get().SetRenderer(m_Renderer);
    SceneManager::Get().SetAssetProvider(provider); //SceneManager에 ResourceManager를 참조하는 멤버 넣어줌 
    SceneManager::Get().Initalize(m_Scene_map); //받은 map 멤버로 시작 



    //m_Dummy = make_unique<Dummy>(); //예시
    m_timer = make_unique<GameTimer>();
    m_timer->Start();
    return true;
}





