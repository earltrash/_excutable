#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Status.h"


//���� �Ľ̰� Ŭ���� ������ ����?
#include "json.hpp"
#include "ItemGlobal.h"
using namespace std;

using json = nlohmann::json;

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // �׳� ������ ���� �;���...

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
	//���콺 Ŭ���� �ް� �ҰŴϱ� 
	Item(ItemCommonData data); //stat�� �־�����, �� �޾ƿ��� �Ÿ� ��� �ϸ� ������
	virtual ~Item() = default;

	void Worked(const MSG& msg) override;

public:  
	ItemCommonData m_data{};
	Need_Moment Momnet;

protected:
	//�ϴ� bounds�� �ӽ�
	RECT m_bounds = { 0,0, 10, 10 }; //transform + mapping �Ǵ� asset�� frame width height���� ���� �ϱ� ��. 
	RECT Fixed_bounds = {0,0, 10, 10};// transform ���̶� ��ġ�� m_bounds �ǰ� �Ϸ��� ��,
	//transform ��ü�� inventory�� �Ҵ����ִ� ����. ���� 

};


