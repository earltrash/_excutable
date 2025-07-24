#pragma once
#include "pch.h"
#include "Component.h"
#include "TMHelper.h"


using Vec2 = MYHelper::Vector2F; //��Ȯ���� rect�� �ʿ��� �� ���� ��. ���� 


class Collider : public Component
{
public:
	Collider(Vec2 pos, SIZE size) : m_top_left(pos), m_size(size) {};
	~Collider() = default;

	void SetCollider(SIZE changed) { m_size = changed; }
	


private:

	Vec2 m_top_left;
	SIZE m_size;
};