#pragma once
#include "pch.h"
#include "Flight.h"



class Player : public Flight {

public:
	Player(RECT bounds);
	//listner keyó�� �ѱ��. 
	~Player() {};


	void Shoot() override;
	void Dead() override;
	void GetShoot() override;

	void Move(const MSG& msg);
//�޽��� �ް� ����� �����Լ��� ����� �ɵ�.
};