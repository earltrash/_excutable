#pragma once
#include "pch.h"
#include "Object.h"

class MSG_Reciver : public Object
{
protected:
	MSG_Reciver() {}; ////component�����ͼ� messenger ��Ͻ�Ű��
	virtual ~MSG_Reciver() = default; //���� ����Ʈ �����Ͷ� ����

protected:
	virtual void Worked(const MSG& msg) {};
	
};