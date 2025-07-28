#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Dispatcher.h"
#include "CallbackType.h"
#include "MouseListenerComponent.h" //������ ���ݾ�

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // �׳� ������ ���� �;���...

class Button : public MSG_Reciver
{
public:
	Button(RECT bounds, Callback cb);
	~Button();

public:

	void Worked(const MSG& msg) override; //��ư ������ �� �̰� �־��ָ� ��.

private:
	RECT m_bounds; //��� Ŭ�� �ٿ�尡 �ʿ��ϱ� �ϴϱ�, �÷��̾ �������� �ʳ�?
	Callback m_callback;
	
};

