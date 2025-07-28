#include "Item.h"
#include "MouseListenerComponent.h"
#include "InputManager.h"
#include "Dispatcher.h"

//transform�� �ֱ� �� �ٵ� 
Item::Item(fundamentalStatus stat, string name, string desc,
	int itemId, bool isSyn, bool isEnforce, ItemType type) : m_stat(stat), name(name), description(desc),
	itemId(itemId), isSynthesis(isSyn), isEnforce(isEnforce), type(type)
{
	InputManager::Get().m_broadcaster->AddListener(
		this->AddComponent<MouseListenerComponent>([this](const MSG& msg) {
			this->Worked(msg); }));
	//��Ȱ��ȭ �ѹ����� �ڴ�. //�̰� Ų �ֵ��� �׳� return ���������� �ŷ� ������ �����̶� transform ���ٵ� ���ϰ� �� ����. ���� 
}


#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) // �׳� ������ ���� �;���...

bool isDragging = false;
POINT dragStart = {};


void Item::Worked(const MSG& msg) //�׷� ũ�� ��ü�� size�ڳ�, ��� Itemtype �� ���� �б� ������ �� ��. ���� Ŭ��, �巡��, 
{

    if (!activated)  
        return;

    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };

   
    // return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

    if (PtInRect(&m_bounds, CORD)) //Item ���� ��쿡�� ��ǥ���� ������ ��ȿ�� �� �ٰ� �ƴ� 
    {
        switch (msg.message)
        {
        case WM_LBUTTONDBLCLK: //���� Ŭ��
        {
            if (IsConsumable())
                std::cout << "���� ��뿡 ���� �Լ� �����ϱ�" << endl;
            //�ƴ� ��� equipment�ϱ� ��� ���� �� ��� ����� ��쿡�� swap ��Ű��. 
        }
            break;

        case WM_MOUSEMOVE:
        {
            if (isDragging)
            {
                POINT current = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
                //������Ʈ�� m_transform�� ���� current������ ���� ���Ѿ� ��. 
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
                    std::cout << "���⼭ ��ȭ ���ñ� ó�� �ϼ���" << endl;
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
        std::cout << "�׷��� ���µ���" << std::endl;
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
        std::cout << "�׷��� ���µ���" << std::endl;
        break;


    }
}
