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

    hr = ComInit(); // Com ��ü ���� 
    assert(SUCCEEDED(hr));

    hr = ModuleInit();     // �Ŵ����� �ʱ�ȭ�� �� �ܰ迡�� ���� : ���ҽ� load & ��� ��� �ʱ�ȭ �� ����
    assert(SUCCEEDED(hr));

    //etc

    std::cout << "Init ������" << std::endl; 
   
}


void M_Core::Run() //���� ���, ���ν����� InputManager�� ���� �ʿ�� ����. + ���ν����� ���� ����� ������ �־ MSG ����ü ��ü�� ������ �� ���⿡ ���⼭ Input ó��
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //Ư�� �޽����� ó���ؾ� ��. 
        {
            if (!InputManager::Get().MsgCheck(msg)) //Inputmanager���� ó���ϴ� �ָ� �갡 ��, ��ǲó���� ���⼭ ��. 
            {
                TranslateMessage(&msg); //�������� ���ν�����...
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
    FixedUpdate(); //���� �� �Ǵ�ó�� 
    Update();  // event state
    Render(); //����
}


void M_Core::FixedUpdate() //�ð� ó�� 
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

bool M_Core::ComInit()  //DX11 ���� 
{
    m_Renderer = make_shared<D2DRenderer>();
    m_Renderer->Initialize(m_hWnd);
    ID3D11Device* pd3dDevice = m_Renderer->GetD3DDevice();
    return true;

    
} //�ϴ� ���� 

bool M_Core::ModuleInit()
{

    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    std::wcout << L"[exe ��ġ] " << exePath << std::endl;


    InputManager::Get().m_broadcaster = make_unique<EventDispatcher>(); //�̰� ����� �ϳ� ������ 
    if (!InputManager::Get().m_broadcaster)
    {
        std::cout << "broadcaster �Ҵ� �ȵ�" << std::endl;
        return false;
    }

    m_resourceManager = make_unique<ResourceManager>();
    //m_resourceManager->AssetLoad(m_Renderer , m_resourceManager->GetAbsoluteResourcePathA() );
     m_resourceManager->AssetLoad(m_Renderer ,"Resource");

    auto provider = std::make_shared<AssetProvider>(m_resourceManager);



    m_Scene_map = make_shared<unordered_map<SceneInfo, shared_ptr<SceneStandard>>>();  //Core�� UPdate�� ������ �ϴ�
    SceneManager::Get().SetRenderer(m_Renderer);
    SceneManager::Get().SetAssetProvider(provider); //SceneManager�� ResourceManager�� �����ϴ� ��� �־��� 
    SceneManager::Get().Initalize(m_Scene_map); //���� map ����� ���� 



    //m_Dummy = make_unique<Dummy>(); //����
    m_timer = make_unique<GameTimer>();
    m_timer->Start();
    return true;
}





