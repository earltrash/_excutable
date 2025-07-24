#pragma once
#include "pch.h"
#include "Dispatcher.h"
#include "MouseListener.h" //�̰� �� �޾ƾ� �ϴ°� ���ŷӱ� �ϳ�...

using RawEventCallback = std::function<void(const MSG&)>;


class Dummy 
{
public:
	Dummy();
	~Dummy() { std::cout << "Dummy ���" << std::endl; }

public:
	std::unique_ptr<MouseListener> m_DummyAdapter = nullptr;
};