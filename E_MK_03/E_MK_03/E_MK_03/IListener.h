#pragma once
#include "pch.h"
#include "CallbackType.h"

// Event-Listener 패턴

class IListener {

public:
	virtual ~IListener() {}
	virtual void _OnEvent(const MSG& msg){}
	virtual bool Matches(const MSG& msg) const = 0;  // 관심 있는 메시지만 받게
};