#pragma once
#include "pch.h"
#include "Object.h"

class UI_Standard : public Object
{
protected:
	UI_Standard() {}; ////component�����ͼ� messenger ��Ͻ�Ű��
	virtual ~UI_Standard() = default; //���� ����Ʈ �����Ͷ� ����

protected:
	virtual void Worked(const MSG& msg) {};


};