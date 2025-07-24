#pragma once
#include "pch.h"
#include "Dispatcher.h"
#include "MouseListener.h" //이걸 다 받아야 하는게 번거롭긴 하네...

using RawEventCallback = std::function<void(const MSG&)>;


class Dummy 
{
public:
	Dummy();
	~Dummy() { std::cout << "Dummy 사망" << std::endl; }

public:
	std::unique_ptr<MouseListener> m_DummyAdapter = nullptr;
};