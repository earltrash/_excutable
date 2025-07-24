#pragma once
#include "pch.h"
#include "Dispatcher.h"
using namespace std;




class InputManager { //얘 결국 싱글톤 안 쓸거면 얘 멤버를 싱글톤 하는 게 구조상 더 나아보이긴 함. 얘는 뭐랄까 관제탑 역할만 하는 애라. 

private: 
	InputManager();
	~InputManager();
public:
	static InputManager& Get();
	void IgnoreNextInput();
	bool MsgCheck(MSG& msg); //InputManager에서 다루는 입력이 아닌 경우는 프로시저로 넘김. 
	void Clean();

public:
	unique_ptr<EventDispatcher> m_broadcaster = nullptr;

	bool m_ignoreNextInput = false;
	UINT m_ignoredMsg = 0;         // 무시할 메시지 종류
	bool m_ignoreAnyMessage = false; // true면 종류 무관하고 한 번 무시

public:
	void SetInCallback(bool flag) { m_isInCallback = flag; }
	bool IsInCallback() const { return m_isInCallback; }
	bool m_isInCallback = false;
};






