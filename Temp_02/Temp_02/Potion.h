#pragma once
#include "Item.h"

class Potion : public Item
{
public:
	Potion(const ItemCommonData& data, const json& j);

	int GetMuch() { return much; }
	void Worked(const MSG& msg) override;

private:
	int much =0; //�󸶳� �÷��� ����? 

};

