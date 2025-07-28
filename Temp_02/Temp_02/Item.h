#pragma once
#include "pch.h"
#include "MSG_Reciver.h"
#include "Status.h"

using namespace std;

enum class ItemType
{
	Wearable,       // ��
	CONSUMABLE,  // �Ҹ�ǰ
};

class Item : public MSG_Reciver //
{
public:
	//���콺 Ŭ���� �ް� �ҰŴϱ� 
	Item(fundamentalStatus stat, string name, string desc, int itemId,
		bool isSyn, bool isEnforce, ItemType type); //stat�� �־�����, �� �޾ƿ��� �Ÿ� ��� �ϸ� ������
	~Item() = default;


	void Worked(const MSG& msg) override;

private:
	int itemId;                                       // ������ ���� Ű
	fundamentalStatus m_stat{};
	string name;                                
	string description;
	bool isSynthesis;                                 // �ռ� ���� ����
	bool isEnforce;                                   // ��ȭ ���� ����
	ItemType type;

};


