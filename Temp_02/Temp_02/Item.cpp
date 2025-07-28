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


void Item::Worked(const MSG& msg) //그럼 크기 자체는 size겠네 
{

	POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
	////아이템 자체는 클릭 처리를 어떻게 다뤄야 하지? 
	//if (PtInRect(&m_bounds, CORD) && !already_Done)
	//{
	//	already_Done = true;
	//	m_enabled = false;

	//	if (m_callback) {
	//		InputManager::Get().SetInCallback(true);
	//		m_callback(msg);
	//		InputManager::Get().SetInCallback(false);
	//	}
	//}



}
