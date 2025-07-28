#pragma once
#include "pch.h"
#include "Object.h"


class Flight : public Object
{
public:
	Flight(RECT bounds) { //ADD COMPONENT <TRANSFORM> ui는 따로 관리 할게. 

		SetPosition({ bounds.left, bounds.top });

	};
	~Flight() {};

protected:
	virtual void Shoot() {};
	virtual void Dead() {};
	virtual void GetShoot() {};

private:
	int Life =1;
};