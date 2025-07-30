#pragma once
#include "Item.h"

class Wearable : public Item
{
public:
	Wearable(const ItemCommonData& data, const json& j);

 void SetStat(const Status_fundamental& statName, int value);
 int GetStat(const Status_fundamental& statName) const;
 void SetPart(const Wearable_part& Part);
 void Worked(const MSG& msg) override;



 //위 둘은 ItemGlobal 참고 
private:
fundamentalStatus m_stat{}; //장비의 스텟 
Wearable_part m_part; //장비 중에서도 어떤 파츠인지

};

//void Item::SetStat(const Status_fundamental& statName, int value)
//{
//    switch (statName)
//    {
//    case Status_fundamental::power:
//        m_stat.power == value;
//        break;
//    case Status_fundamental::agile:
//        m_stat.agile == value;
//        break;
//    case Status_fundamental::intelligence:
//        m_stat.intelligence == value;
//        break;
//    case Status_fundamental::luck:
//        m_stat.luck == value;
//        break;
//    default:
//        std::cout << "그런건 없는뎁쇼" << std::endl;
//        break;
//    }
//}
//
//float Item::GetStat(const Status_fundamental& statName) const
//{
//    switch (statName)
//    {
//    case Status_fundamental::power:
//        return m_stat.power;
//    case Status_fundamental::agile:
//        return m_stat.agile;
//    case Status_fundamental::intelligence:
//        return m_stat.intelligence;
//    case Status_fundamental::luck:
//        return m_stat.luck;
//    default:
//        std::cout << "그런건 없는뎁쇼" << std::endl;
//        break;
//
//
//    }