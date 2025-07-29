#pragma once
#include "pch.h"
#include "Object.h"

class MSG_Reciver : public Object
{
protected:
	MSG_Reciver() {}; ////component가져와서 messenger 등록시키기
	virtual ~MSG_Reciver() = default; //차피 스마트 포인터라 ㄱㅊ

protected:
	virtual void Worked(const MSG& msg) {};
	
};