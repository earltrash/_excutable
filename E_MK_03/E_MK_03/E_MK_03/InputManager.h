#pragma once
#include "pch.h"
#include "Dispatcher.h"
using namespace std;

class InputManager { //�� �ᱹ �̱��� �� ���Ÿ� �� ����� �̱��� �ϴ� �� ������ �� ���ƺ��̱� ��. ��� ������ ����ž ���Ҹ� �ϴ� �ֶ�. 

private: 
	InputManager();
	~InputManager();
public:
	static InputManager& Get();
	bool MsgCheck(MSG& msg); //InputManager���� �ٷ�� �Է��� �ƴ� ���� ���ν����� �ѱ�. 
	void Clean();

public:
	unique_ptr<EventDispatcher> m_broadcaster = nullptr;


};






