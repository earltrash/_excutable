#pragma once
#include "Item.h"

class Material : public Item
{
public:
	Material(const ItemCommonData& data, const json& j);
	void Worked(const MSG& msg) override;
	

private:
	fundamentalStatus m_stat{};


};