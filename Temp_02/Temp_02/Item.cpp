#include "Item.h"
#include "MouseListenerComponent.h"
#include "InputManager.h"
#include "Dispatcher.h"

//transform이 있긴 할 텐데 
Item::Item(fundamentalStatus stat, string name, string desc,
	int itemId, bool isSyn, bool isEnforce, ItemType type) : m_stat(stat), name(name), description(desc),
	itemId(itemId), isSynthesis(isSyn), isEnforce(isEnforce), type(type)
{
	InputManager::Get().m_broadcaster->AddListener(
		this->AddComponent<MouseListenerComponent>([this](const MSG& msg) {
			this->Worked(msg); }));
	//비활성화 켜버려야 겠다. //이거 킨 애들은 그냥 return 때려버리는 거로 랜더랑 연산이랑 transform 접근도 못하게 할 거임. ㅇㅇ 
}


#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // 그냥 멋지게 쓰고 싶었다...

bool isDragging = false;
POINT dragStart = {};


void Item::Worked(const MSG& msg) //그럼 크기 자체는 size겠네, 멤버 Itemtype 에 따라서 분기 나눠야 할 듯. 더블 클릭, 드래그, 
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
            if (IsConsumable())
                std::cout << "물약 사용에 대한 함수 실행하기" << endl;
            //아닌 경우 equipment니깐 장비 착용 및 장비 착용된 경우에는 swap 시키기. 
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
            if (isDragging)
            {
                isDragging = false;
                if (IsMateral())
                    std::cout << "여기서 강화 뭐시기 처리 하세요" << endl;
            }
            break;
        }
        default:
            break;
      }
    }
}

bool Item::IsEquipment() const
{
    return type == ItemType::Wearable;
}

bool Item::IsConsumable() const
{
    return type == ItemType::CONSUMABLE;

}

bool Item::IsMateral() const
{
    return type == ItemType::MATERIAL;
}

void Item::SetStat(const Status_fundamental& statName, int value)
{
    switch (statName)
    {
    case Status_fundamental::power:
        m_stat.power == value;
        break;
    case Status_fundamental::agile:
        m_stat.agile == value;
        break;
    case Status_fundamental::intelligence:
        m_stat.intelligence == value;
        break;
    case Status_fundamental::luck:
        m_stat.luck == value;
        break;
    default:
        std::cout << "그런건 없는뎁쇼" << std::endl;
            break;
    }
}

float Item::GetStat(const Status_fundamental& statName) const
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
        std::cout << "그런건 없는뎁쇼" << std::endl;
        break;


    }
}
