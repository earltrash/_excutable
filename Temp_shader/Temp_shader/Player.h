#pragma once
#include "pch.h"
#include "Flight.h"



class Player : public Flight {

public:
	Player(RECT bounds);
	//listner keyó�� �ѱ��. 
	~Player() {};
	void Move(const MSG& msg);
};