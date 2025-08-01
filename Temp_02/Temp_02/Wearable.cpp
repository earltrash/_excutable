#include "Wearable.h"






Wearable::Wearable(const ItemCommonData& data, const json& j) : Item(data)
{
    for (const auto& s : j["stats"]) //여러개인 경우가 있으니깐 
    {
        std::string statName = s["stat"]; //이거 enum으로 바꿔야 할 듯. ㅇㅇ 
        float amount = s["amount"];
       SetStat(StringToF(statName), amount);
    }

    if (j.contains("part"))
    {
        std::string part = j["part"];
        m_part = StringToWP(part);
    }



}

void Wearable::SetStat(const Status_fundamental& statName, int value)
{
    switch (statName)
    {
    case Status_fundamental::power:
     m_stat.power = value; 
     break;
    case Status_fundamental::agile:
        m_stat.agile = value;
        break;
    case Status_fundamental::intelligence:
        m_stat.intelligence = value;
        break;
    case Status_fundamental::luck:
        m_stat.luck = value;
        break;
    }
}

int Wearable::GetStat(const Status_fundamental& statName) const
{
    switch (statName)
    {
    case Status_fundamental::power:
        return m_stat.power;
       
    case Status_fundamental::agile:
        return m_stat.agile;
       
    case Status_fundamental::intelligence:
        return m_stat.intelligence;
       
    case Status_fundamental::luck:
        return m_stat.luck;
       
    default:
        return 0;
    }
}

void Wearable::SetPart(const Wearable_part& Part)
{
    switch (Part)
    {
    case Wearable_part::Weapon:
        m_part = Wearable_part::Weapon;
        break;
    case Wearable_part::Shoes:
        m_part = Wearable_part::Shoes;
        break;
    case Wearable_part::EarRing:
        m_part = Wearable_part::EarRing;
        break;
    case Wearable_part::Neckless:
        m_part = Wearable_part::Neckless;
        break;
    case Wearable_part::Glove:
        m_part = Wearable_part::Glove;
        break;
    case Wearable_part::Under:
        m_part = Wearable_part::Under;
        break;
    case Wearable_part::Upper:
        m_part = Wearable_part::Upper;
        break;
    case Wearable_part::Helmet:
        m_part = Wearable_part::Helmet;
        break;
    default:
        std::cout << "너는 어디 장비임??" << endl;
   
    }
}

void Wearable::Worked(const MSG& msg)
{
    if (!activated)
        return;

    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };


    // return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

    if (PtInRect(&m_bounds, CORD)) //Item 같은 경우에는 좌표값이 영역에 유효한 게 다가 아님 
    {
        switch (msg.message)
        {
        case WM_LBUTTONDBLCLK: //더블 클릭
        {
           //swap 호출 
        }
        break;

        case WM_MOUSEMOVE:
        {
            if (isDragging)
            {
                POINT current = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
                //오브젝트의 m_transform을 현재 current값으로 변경 시켜야 함. 
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {
            isDragging = true;
        }
        break;
        case WM_LBUTTONUP:
        {
            {
                isDragging = false;
                
            }
            break;
        }
        default:
            break;
        }
    }
}
