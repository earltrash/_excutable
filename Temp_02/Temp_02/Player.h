#pragma once
#include "pch.h"
#include "Flight.h"



class Player : public Flight {

public:
	Player(RECT bounds);
	//listner key처리 넘기기. 
	~Player() {};
	void Move(const MSG& msg);
};