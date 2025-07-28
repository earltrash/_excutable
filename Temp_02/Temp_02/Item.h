#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Status.h"

using namespace std;

enum class ItemType
{
	Wearable,       // 방어구
	CONSUMABLE,  // 소모품
};

class Item : public MSG_Reciver //
{
public:
	//마우스 클릭도 받게 할거니깐 
	Item(fundamentalStatus stat, string name, string desc, int itemId,
		bool isSyn, bool isEnforce, ItemType type); //stat을 넣어주자, 값 받아오는 거를 어떻게 하면 좋을까
	~Item() = default;


	void Worked(const MSG& msg) override;

private:
	int itemId;                                       // 아이템 고유 키
	fundamentalStatus m_stat{};
	string name;                                
	string description;
	bool isSynthesis;                                 // 합성 가능 여부
	bool isEnforce;                                   // 강화 가능 여부
	ItemType type;

};


