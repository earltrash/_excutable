#include "pch.h"
#include "Scene.h"
#include "SceneFactory.h"

SceneStandard::SceneStandard(string name, Provider provider, Renderer renderer)
{
	m_name = name;
	SetAssetProvider( provider);
	SetRenderer(  renderer);

}

void SceneStandard::Initalize()
{
	GetAsset(m_name);
	SceneFactory::Get().InitScene(m_name, *this);
	AssetMapping();
}

void SceneStandard::Clean() //다형성이 필요해지면 이거 하위에서 구체화 해도 ㄱㅊClean()
{
	std::cout << "정리시작" << std::endl;
	for (const auto& [name, obj] : m_gameObjects)
	{
		obj->Delete(); //object-> 개인 map데이터 삭제 (name animation_clip)

		m_curSprites[obj.get()].Delete(); //얘가 갖고 있는 주소를 없앰
		m_curSprites.erase(obj.get()); 
	}
	m_gameObjects.clear();
	m_curSprites.clear();
	SceneAssets.clear();
}

void SceneStandard::Update()
{
	for (auto& e : m_gameObjects)
	{
		e.second->Update();
	}
}


void SceneStandard::LogicUpdate(float delta) //키 입력을 해서 캐릭터의 sprite image가 변경되는 경우-> dirty, dirty가 되면 state에 따라서 bitmap을 수정.
{
		
	for ( auto& [obj, ap] : m_curSprites)//Object 위치에 접근을 해야 하니깐, Object 개수만큼 반복, 
	{
		
		ap.Update(delta);
	}

}



void SceneStandard::Render() //UI 렌더
{
	assert(m_renderer);

	MAT3X2F cameraTM = UnityCamera::GetCamera().GetViewMatrix(); //매번 업데이트가 되니깐 
	MAT3X2F renderTM = MYTM::MakeRenderMatrix(true); // 카메라 위치 렌더링 매트릭스
	MAT3X2F finalTM = renderTM * cameraTM;

	m_renderer->RenderBegin();
	
	m_renderer->SetTransform(finalTM);
	
	for (const auto& [obj, ap] : m_curSprites)
	{
	
		D2D1::Matrix3x2F worldTM = obj->GetTransform().GetWorldMatrix(); 
		D2D1::Matrix3x2F finalTM = renderTM * worldTM * cameraTM;
		m_renderer->SetTransform(finalTM);

		const Frame& frame = ap.GetCurrentFrame();
		const auto& srcU = frame.srcRect;

		D2D1_RECT_F srcRect = D2D1::RectF(
			static_cast<float>(srcU.left),
			static_cast<float>(srcU.top),
			static_cast<float>(srcU.right),
			static_cast<float>(srcU.bottom)
		);

		D2D1_RECT_F destRect = {
			0.f,
			0.f,
			static_cast<float>(srcU.right - srcU.left),
			static_cast<float>(srcU.bottom - srcU.top)
		};

		m_renderer->SetTransform(finalTM); // Object 위치
		m_renderer->DrawBitmap(ap.GetClip()->GetBitmap(), destRect,  srcRect, 1);
	}
	m_renderer->RenderEnd();

}

void SceneStandard::AssetMapping()
{
	for (auto& [name, obj] : m_gameObjects) { //map의 auto 반복문은 이런 구조...
		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) { //게임 오브젝트의 이름과 clip_Asset의 Name과 같은 경우 (json parssing)
				obj->AddClip(asset.Ani_Name, asset.clip); //한 오브젝트의 여러 clip들을 넣어줌. 

				if (asset.Ani_Name == "Idle") //일단 임시로 이렇게 씀. 
					obj->SetCurrentClip(asset.clip);
			}
		}
	}

	for (const auto& [name, obj] : m_gameObjects) //선택된 파일의 CLIP 주소를 SPRITEANIMATOR에 넣어 줌. & CURSPRITE에다가도, 
	{
		SpriteAnimator ap;
		ap.SetClip(&obj->GetCurrentClip()); //
		m_curSprites.emplace(obj.get(), ap); //그래서 VECTOR로 관리하는 거고 
	}
	return ;
}



