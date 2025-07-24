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
	void IgnoreNextInput();
	bool MsgCheck(MSG& msg); //InputManager���� �ٷ�� �Է��� �ƴ� ���� ���ν����� �ѱ�. 
	void Clean();

public:
	unique_ptr<EventDispatcher> m_broadcaster = nullptr;

	bool m_ignoreNextInput = false;
	UINT m_ignoredMsg = 0;         // ������ �޽��� ����
	bool m_ignoreAnyMessage = false; // true�� ���� �����ϰ� �� �� ����

public:
	void SetInCallback(bool flag) { m_isInCallback = flag; }
	bool IsInCallback() const { return m_isInCallback; }
	bool m_isInCallback = false;
};






