#include "pch.h"
#include "Scene.h"
#include "Camera2D.h"

void SceneStandard::Initalize()
{

}

void SceneStandard::Clean() //�������� �ʿ������� �̰� �������� ��üȭ �ص� ����
{
	std::cout << "��������" << std::endl;
	for (const auto& [name, obj] : m_gameObjects)
	{
		obj->Delete(); //object-> ���� map������ ���� (name animation_clip)

		m_curSprites[obj.get()].Delete(); //�갡 ���� �ִ� �ּҸ� ����
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


void SceneStandard::LogicUpdate(float delta) //Ű �Է��� �ؼ� ĳ������ sprite image�� ����Ǵ� ���-> dirty, dirty�� �Ǹ� state�� ���� bitmap�� ����.
{
		
	for ( auto& [obj, ap] : m_curSprites)//Object ��ġ�� ������ �ؾ� �ϴϱ�, Object ������ŭ �ݺ�, 
	{
		
		ap.Update(delta);
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

		m_renderer->SetTransform(finalTM); // Object ��ġ
		m_renderer->DrawBitmap(ap.GetClip()->GetBitmap(), destRect,  srcRect, 1);
	}
	m_renderer->RenderEnd();

}

