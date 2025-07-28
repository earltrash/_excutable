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

void SceneStandard::Clean() 
{
	m_gameObjects.clear();
	SceneAssets.clear();
}

void SceneStandard::Update()
{
	for (auto& e : m_gameObjects)
	{
		e.second->Update(); //일단 뭐 없긴 함. 
	}
}


void SceneStandard::LogicUpdate(float delta) 
{
		
	for ( auto& [name, obj] : m_gameObjects) //Object 위치에 접근을 해야 하니깐, Object 개수만큼 반복, 
	{
		obj->GetSpriteRenderer().Update(delta); //sprite update 
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
	for (const auto& [Name, obj] : m_gameObjects)
	{
		D2D1::Matrix3x2F worldTM = obj->GetTransform().GetWorldMatrix();
		D2D1::Matrix3x2F finalTM = renderTM * worldTM * cameraTM;
		m_renderer->SetTransform(finalTM);

		const Frame& frame = obj->GetSpriteRenderer().GetCurrentFrame();
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
		m_renderer->DrawBitmap(obj->GetSpriteRenderer().GetCurrentClip().GetBitmap(), destRect, srcRect, 1);
	}
	m_renderer->RenderEnd();
}

void SceneStandard::AssetMapping()
{
	//for (auto& [name, obj] : m_gameObjects) { //map의 auto 반복문은 이런 구조...
	//	for (const auto& asset : SceneAssets) {
	//		if (asset.Name == name) { 
	//			obj->GetSpriteRenderer().AddClip(asset.Ani_Name, asset.clip);
	//			if (asset.Ani_Name == "Idle") 
	//				obj->GetSpriteRenderer().SetCurrentClip(&asset.clip); 
	//		}
	//	}
	//}
	

	for (auto& [name, obj] : m_gameObjects) {
		bool hasIdleClip = false;
		AnimationClip* idleClip = nullptr;

		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) {
				// 각 애니메이션 클립을 개별적으로 추가
				obj->GetSpriteRenderer().AddClip(asset.Ani_Name, asset.clip);

				// Idle 클립 찾기
				if (asset.Ani_Name == "Idle") {
					hasIdleClip = true;
					idleClip = const_cast<AnimationClip*>(&asset.clip);
				}
			}
		}

		// Idle 클립이 있으면 기본 클립으로 설정
		if (hasIdleClip && idleClip) {
			obj->GetSpriteRenderer().SetCurrentClip(idleClip);
		}
	}


	return;

}



