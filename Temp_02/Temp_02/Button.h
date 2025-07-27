#pragma once
#include "pch.h"
#include "UI_Standard.h"
#include "Dispatcher.h"
#include "CallbackType.h"
#include "MouseListenerComponent.h" //어차피 있잖아

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // 그냥 멋지게 쓰고 싶었다...

class Button : public UI_Standard
{
public:
	Button(RECT bounds, Callback cb);
	~Button();

public:

	void Worked(const MSG& msg) override; //버튼 생성할 때 이거 넣어주면 끝.

	//키 활성 비활성화
	void SetEnabled(bool enabled) { m_enabled = enabled; }
	bool IsEnabled() const { return m_enabled; }

private:
	RECT m_bounds; //얘는 클릭 바운드가 필요하긴 하니깐, 플레이어도 동일하지 않나?
	Callback m_callback;
	bool m_enabled = true;
	bool already_Done = false;
};

