#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Status.h"

using namespace std;

enum class ItemType
{
	Wearable,       // ��
	CONSUMABLE,  // �Ҹ�ǰ
	MATERIAL     // ��ȭ�� 
};

class Item : public MSG_Reciver //
{
public:
	//���콺 Ŭ���� �ް� �ҰŴϱ� 
	Item(fundamentalStatus stat, string name, string desc, int itemId,
		bool isSyn, bool isEnforce, ItemType type); //stat�� �־�����, �� �޾ƿ��� �Ÿ� ��� �ϸ� ������
	~Item() = default;
	void Worked(const MSG& msg) override;


public:
	//���콺 �Է¹ް�, Ư���� ���� Ŭ�� �� ��,�� �巡��? �ÿ� Ÿ������ �̸� �Ǵ���! 
	bool IsEquipment() const;
	bool IsConsumable() const;
	bool IsMateral() const;

	void SetStat(const Status_fundamental& statName, int value);
	float GetStat(const Status_fundamental& statName) const;

private:
	int itemId;                                       // ������ ���� Ű
	fundamentalStatus m_stat{};
	string name;                                
	string description;
	bool isSynthesis;                                 // �ռ� ���� ����
	bool isEnforce;                                   // ��ȭ ���� ����
	ItemType type;


	RECT m_bounds; //transform + mapping �Ǵ� asset�� frame width height���� ���� �ϱ� ��. 
	RECT Fixed_bounds = {0,0, 10, 10};// transform ���̶� ��ġ�� m_bounds �ǰ� �Ϸ��� ��,
	//transform ��ü�� inventory�� �Ҵ����ִ� ����. ���� 

};


