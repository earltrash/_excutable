#pragma once
#include "pch.h"
#include "Object.h"

class UI_Standard : public Object
{
protected:
	UI_Standard() {}; ////component가져와서 messenger 등록시키기
	virtual ~UI_Standard() = default; //차피 스마트 포인터라 ㄱㅊ

protected:
	virtual void Worked(const MSG& msg) {};


};