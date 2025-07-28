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
		e.second->Update(); //�ϴ� �� ���� ��. 
	}
}


void SceneStandard::LogicUpdate(float delta) 
{
		
	for ( auto& [name, obj] : m_gameObjects) //Object ��ġ�� ������ �ؾ� �ϴϱ�, Object ������ŭ �ݺ�, 
	{
		obj->GetSpriteRenderer().Update(delta); //sprite update 
	}

}


void SceneStandard::Render() //UI ����
{
	assert(m_renderer);

	MAT3X2F cameraTM = UnityCamera::GetCamera().GetViewMatrix(); //�Ź� ������Ʈ�� �Ǵϱ� 
	MAT3X2F renderTM = MYTM::MakeRenderMatrix(true); // ī�޶� ��ġ ������ ��Ʈ����
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

		m_renderer->SetTransform(finalTM); // Object ��ġ
		m_renderer->DrawBitmap(obj->GetSpriteRenderer().GetCurrentClip().GetBitmap(), destRect, srcRect, 1);
	}
	m_renderer->RenderEnd();
}

void SceneStandard::AssetMapping()
{
	//for (auto& [name, obj] : m_gameObjects) { //map�� auto �ݺ����� �̷� ����...
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
				// �� �ִϸ��̼� Ŭ���� ���������� �߰�
				obj->GetSpriteRenderer().AddClip(asset.Ani_Name, asset.clip);

				// Idle Ŭ�� ã��
				if (asset.Ani_Name == "Idle") {
					hasIdleClip = true;
					idleClip = const_cast<AnimationClip*>(&asset.clip);
				}
			}
		}

		// Idle Ŭ���� ������ �⺻ Ŭ������ ����
		if (hasIdleClip && idleClip) {
			obj->GetSpriteRenderer().SetCurrentClip(idleClip);
		}
	}


	return;

}



