#pragma once
#include "pch.h"
#include "Component.h"


class ListenerComponent : public Component //�ణ �������̽� �������θ� ����� ���� 
{
public:
	ListenerComponent() = default;
	virtual ~ListenerComponent() = default;

	virtual void _OnEvent(const MSG& msg) {}
	virtual bool Matches(const MSG& msg) const = 0;  // ���� �ִ� �޽����� �ް�
};
