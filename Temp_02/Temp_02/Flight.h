#pragma once
#include "pch.h"
#include "Object.h"


class Flight : public Object
{
public:
	Flight(RECT bounds) { //ADD COMPONENT <TRANSFORM> ui�� ���� ���� �Ұ�. 

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