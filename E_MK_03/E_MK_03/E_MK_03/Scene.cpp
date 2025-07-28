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

using Vec2F = MYHelper::Vector2F;

void SceneStandard::Render() //UI ����
{
	assert(m_renderer);
	m_renderer->RenderBegin();
	
	for (const auto& [Name, obj] : m_gameObjects)
	{
		const Frame& frame = obj->GetSpriteRenderer().GetCurrentFrame();
		const auto& srcU = frame.srcRect;

		D2D1_RECT_F srcRect = D2D1::RectF(
			static_cast<float>(srcU.left),
			static_cast<float>(srcU.top),
			static_cast<float>(srcU.right),
			static_cast<float>(srcU.bottom)
		);

		const Vec2F& pos = obj->GetTransform().GetPosition(); // ������Ʈ�� ��ġ�� �����´ٰ� ����

		D2D1_RECT_F destRect = {
			pos.x,
			pos.y,
			pos.x + static_cast<float>(srcU.right - srcU.left),
			pos.y + static_cast<float>(srcU.bottom - srcU.top)
		};

		m_renderer->DrawBitmap(obj->GetSpriteRenderer().GetCurrentClip().GetBitmap(), destRect, srcRect, 1);
	}
	m_renderer->RenderEnd();
}

void SceneStandard::AssetMapping()
{
	for (auto& [name, obj] : m_gameObjects) { //map�� auto �ݺ����� �̷� ����...
		for (const auto& asset : SceneAssets) {
			if (asset.Name == name) { 
				obj->GetSpriteRenderer().AddClip(asset.Ani_Name, asset.clip);
				if (asset.Ani_Name == "Idle") 
					obj->GetSpriteRenderer().SetCurrentClip(&asset.clip); 
			}
		}
	}
	


	return;

}



