#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Status.h"


//밑은 파싱과 클래스 오염을 방지?
#include "json.hpp"
#include "ItemGlobal.h"
using namespace std;

using json = nlohmann::json;

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // 그냥 멋지게 쓰고 싶었다...

struct ItemCommonData {
	std::string id;
	std::string name;
	std::string description;
	bool enchantable;
	bool synthesizable;
	Need_Moment Momnet;

};

class Item : public MSG_Reciver //
{
public:
	//마우스 클릭도 받게 할거니깐 
	Item(ItemCommonData data); //stat을 넣어주자, 값 받아오는 거를 어떻게 하면 좋을까
	virtual ~Item() = default;

	void Worked(const MSG& msg) override;

public:  
	ItemCommonData m_data{};
	Need_Moment Momnet;

protected:
	//일단 bounds는 임시
	RECT m_bounds = { 0,0, 10, 10 }; //transform + mapping 되는 asset의 frame width height값이 들어가야 하긴 함. 
	RECT Fixed_bounds = {0,0, 10, 10};// transform 값이랑 합치면 m_bounds 되게 하려고 함,
	//transform 자체는 inventory가 할당해주는 거임. ㅇㅇ 

};


