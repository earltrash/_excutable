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


void Item::Worked(const MSG& msg) //�׷� ũ�� ��ü�� size�ڳ� 
{

	POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
	////������ ��ü�� Ŭ�� ó���� ��� �ٷ�� ����? 
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
