#pragma once
#include "pch.h"
#include "Flight.h"



class Player : public Flight {

public:
	Player(RECT bounds);
	//listner key처리 넘기기. 
	~Player() {};


	void Shoot() override;
	void Dead() override;
	void GetShoot() override;

	void Move(const MSG& msg);
//메시지 받고 출력할 람다함수도 만들면 될듯.
};