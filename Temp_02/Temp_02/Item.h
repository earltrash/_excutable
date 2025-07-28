#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Status.h"

using namespace std;

enum class ItemType
{
	Wearable,       // 방어구
	CONSUMABLE,  // 소모품
	MATERIAL     // 강화서 
};

class Item : public MSG_Reciver //
{
public:
	//마우스 클릭도 받게 할거니깐 
	Item(fundamentalStatus stat, string name, string desc, int itemId,
		bool isSyn, bool isEnforce, ItemType type); //stat을 넣어주자, 값 받아오는 거를 어떻게 하면 좋을까
	~Item() = default;
	void Worked(const MSG& msg) override;


public:
	//마우스 입력받고, 특히나 더블 클릭 할 때,나 드래그? 시에 타입으로 이를 판단함! 
	bool IsEquipment() const;
	bool IsConsumable() const;
	bool IsMateral() const;

	void SetStat(const Status_fundamental& statName, int value);
	float GetStat(const Status_fundamental& statName) const;

private:
	int itemId;                                       // 아이템 고유 키
	fundamentalStatus m_stat{};
	string name;                                
	string description;
	bool isSynthesis;                                 // 합성 가능 여부
	bool isEnforce;                                   // 강화 가능 여부
	ItemType type;


	RECT m_bounds; //transform + mapping 되는 asset의 frame width height값이 들어가야 하긴 함. 
	RECT Fixed_bounds = {0,0, 10, 10};// transform 값이랑 합치면 m_bounds 되게 하려고 함,
	//transform 자체는 inventory가 할당해주는 거임. ㅇㅇ 

};


