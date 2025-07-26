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

	SetPosition({ bounds.left, bounds.top }, { bounds.right - bounds.left, bounds.top - bounds.bottom });

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
            std::cout << "�� ���� �̵�: " << m_transform.GetPosition().x << "\n";
            break;

        case VK_RIGHT:
            m_transform.Translate({ speed, 0.f });
            std::cout << "�� ������ �̵�: " << m_transform.GetPosition().x << "\n";
            break;

        case VK_UP:
            m_transform.Translate({ 0.f, speed });
            std::cout << "�� �� �̵�: " << m_transform.GetPosition().y << "\n";
            break;

        case VK_DOWN:
            m_transform.Translate({ 0.f, -speed });  // Unity�� ��ǥ��: y ���� ���
            std::cout << "�� �Ʒ� �̵�: " << m_transform.GetPosition().y << "\n";
            break;

        default:
            return;
        }
    }
}

