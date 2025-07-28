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
	m_Components.clear();
}

void Object::SetCurrentClip(const AnimationClip& clip)
{
	m_CurrentClip = clip;
}

AnimationClip& Object::GetCurrentClip()
{
	return m_CurrentClip;
}



void Object::SetPosition(POINT position) //�ᱹ size-> frame width-
{	//������Ʈ�� ���� ��� ��ǥ�� �������� �������� ���ϴ� �͵� ������ ���� �� 
	

	GetTransform().SetPosition({
		static_cast<float>(position.x),
		static_cast<float>(position.y)
		});
}

void Object::ComponentClear() { //�Ҹ��ڷ� �̰� �ű��� 

	m_Components.clear();

}

void Object::Delete()
{
	ComponentClear();
}

 Transform& Object::GetTransform()  {
	return m_transform;
}

 SpriteRenderer& Object::GetSpriteRenderer()
 {
	 return m_spriterenderer;
 }
