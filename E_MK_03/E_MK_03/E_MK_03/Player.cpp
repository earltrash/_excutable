#include "pch.h"
#include "Listener.h"
#include "Player.h"
#include "KeyListenerComponent.h"
#include "InputManager.h"
#include "Camera2D.h"

Player::Player(RECT bounds) : Flight(bounds)
{
	
	InputManager::Get().m_broadcaster->AddListener(
		this->AddComponent<KeyListenerComponent>([this](const MSG& msg) {
			this->Move(msg); }));

	SetPosition({ bounds.left, bounds.top }, { bounds.right - bounds.left, bounds.top - bounds.bottom });

}

void Player::Shoot()
{

}

void Player::Dead()
{

}

void Player::GetShoot()
{

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

        default: //ī�޶� ���������� �ϴ� ��� �ξ����ϴ�,.....
            // WASD �Է�
        case 'A':
            UnityCamera::GetCamera().Move(-speed, 0.f);
            std::cout << "[WASD A] ���� �̵�: " << m_transform.GetPosition().x << "\n";
            break;

        case 'D':
            UnityCamera::GetCamera().Move(speed, 0.f);
            std::cout << "[WASD D] ������ �̵�: " << m_transform.GetPosition().x << "\n";
            break;

        case 'W':
            UnityCamera::GetCamera().Move( 0.f, speed );
            std::cout << "[WASD W] �� �̵�: " << m_transform.GetPosition().y << "\n";
            break;

        case 'S':
            UnityCamera::GetCamera().Move(0.f, -speed);
            std::cout << "[WASD S] �Ʒ� �̵�: " << m_transform.GetPosition().y << "\n";
            break;
        case VK_SPACE:
            std::cout << m_transform.GetPosition().x<< "  " << m_transform.GetPosition().y << "\n";

        }
            break;
    }


}


