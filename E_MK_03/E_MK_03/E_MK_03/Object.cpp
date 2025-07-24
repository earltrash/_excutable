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
{	//������Ʈ�� ���� ��� ��ǥ�� �������� �������� ���ϴ� �͵� ������ ���� �� 

	this->size = size; // Collider���� size���� �ǰڴ�. 


	MAT3X2F cameraTM = UnityCamera::GetCamera().GetViewMatrix(); //y�� ����, ȭ�� �߽��� 0,0�� ��ǥ�� // ���⼭ Y�� ����
	cameraTM.Invert(); //���� ��ǥ�� �߽��� �»��.y���� �� 

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
