#pragma once
#include "pch.h"
#include "UI_Standard.h"
#include "Dispatcher.h"
#include "CallbackType.h"
#include "MouseListenerComponent.h" //������ ���ݾ�

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // �׳� ������ ���� �;���...

class Button : public UI_Standard
{
public:
	Button(RECT bounds, Callback cb);
	~Button();

public:

	void Worked(const MSG& msg) override; //��ư ������ �� �̰� �־��ָ� ��.

	//Ű Ȱ�� ��Ȱ��ȭ
	void SetEnabled(bool enabled) { m_enabled = enabled; }
	bool IsEnabled() const { return m_enabled; }

private:
	RECT m_bounds; //��� Ŭ�� �ٿ�尡 �ʿ��ϱ� �ϴϱ�, �÷��̾ �������� �ʳ�?
	Callback m_callback;
	bool m_enabled = true;
	bool already_Done = false;
};

