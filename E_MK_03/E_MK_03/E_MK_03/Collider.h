#pragma once
#include "pch.h"
#include "Component.h"
#include "TMHelper.h"


using Vec2 = MYHelper::Vector2F; //정확히는 rect가 필요할 거 같긴 함. ㅇㅇ 


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