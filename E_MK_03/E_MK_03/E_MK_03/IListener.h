#pragma once
#include "pch.h"
#include "CallbackType.h"

// Event-Listener ����

class IListener {

public:
	virtual ~IListener() {}
	virtual void _OnEvent(const MSG& msg){}
	virtual bool Matches(const MSG& msg) const = 0;  // ���� �ִ� �޽����� �ް�
};