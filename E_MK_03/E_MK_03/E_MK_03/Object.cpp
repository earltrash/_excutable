#pragma once
#include "pch.h"
#include "Object.h"
#include "MouseListenerComponent.h"
#include "KeyListenerComponent.h"
#include "Camera2D.h"

void Object::AddClip(const std::string& aniName, const AnimationClip& clip)
{
	m_clips[aniName] = clip;
}

AnimationClip* Object::GetClip(const std::string& aniName)
{
	auto it = m_clips.find(aniName);
	return (it != m_clips.end()) ? &it->second : nullptr;
}

Object::~Object()
{
	//Delete();
}

void Object::SetCurrentClip(const AnimationClip& clip)
{
	m_CurrentClip = clip;
}

AnimationClip& Object::GetCurrentClip()
{
	return m_CurrentClip;
}



void Object::SetPosition(POINT position, SIZE size)
{	//오브젝트에 따라서 어느 좌표계 기준으로 생성할지 정하는 것도 나쁘지 않을 듯 

	this->size = size; // Collider에서 size쓰면 되겠다. 


	MAT3X2F cameraTM = UnityCamera::GetCamera().GetViewMatrix(); //y값 반전, 화면 중심이 0,0인 좌표계 // 여기서 Y축 반전
	cameraTM.Invert(); //월드 좌표계 중심이 좌상단.y축이 밑 

	D2D1_POINT_2F worldPt = cameraTM.TransformPoint(D2D1::Point2F(static_cast<float>(position.x),
		static_cast<float>(position.y)));

	std::cout << worldPt.x << " " << worldPt.y << endl;

	GetTransform().SetPosition({
		static_cast<float>(worldPt.x),
		static_cast<float>(worldPt.y)
		});
}

void Object::Delete()
{
	m_clips.clear();
	ComponentClear<MouseListenerComponent, KeyListenerComponent>();
}

 Transform& Object::GetTransform()  {
	return m_transform;
}
