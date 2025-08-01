#include "pch.h"
#include "Listener.h"
#include "Player.h"
#include "KeyListenerComponent.h"
#include "InputManager.h"

Player::Player(RECT bounds) : Flight(bounds)
{
	InputManager::Get().m_broadcaster->AddListener(
		this->AddComponent<KeyListenerComponent>([this](const MSG& msg) {
			this->Move(msg); }));

	SetPosition({ bounds.left, bounds.top });

}

void Player::Move(const MSG& msg)
{
    float speed = 10.f;
    //RECT{600, 100, 800, 200})
    switch (msg.message)
    {
    case WM_KEYDOWN:
        switch (msg.wParam)
        {
        case VK_LEFT:
            m_transform.Translate({ -speed, 0.f });
            std::cout << "← 왼쪽 이동: " << m_transform.GetPosition().x << "\n";
            break;

        case VK_RIGHT:
            m_transform.Translate({ speed, 0.f });
            std::cout << "→ 오른쪽 이동: " << m_transform.GetPosition().x << "\n";
            break;

        case VK_UP:
            m_transform.Translate({ 0.f, speed });
            std::cout << "↑ 위 이동: " << m_transform.GetPosition().y << "\n";
            break;

        case VK_DOWN:
            m_transform.Translate({ 0.f, -speed });  // Unity식 좌표계: y 위가 양수
            std::cout << "↓ 아래 이동: " << m_transform.GetPosition().y << "\n";
            break;

        default:
            return;
        }
    }
}

