#include "Item.h"
#include "MouseListenerComponent.h"
#include "InputManager.h"
#include "Dispatcher.h"

//transform이 있긴 할 텐데 
Item::Item(ItemCommonData data) : m_data(data)
{
	InputManager::Get().m_broadcaster->AddListener(
		this->AddComponent<MouseListenerComponent>([this](const MSG& msg) {
			this->Worked(msg); }));
}

void Item::Worked(const MSG& msg) {}







