#pragma once
#include"pch.h"
#include "Button.h"
#include "InputManager.h"
#include "Dispatcher.h"
#include "MouseListenerComponent.h"

Button::Button(RECT bounds, Callback cb) : m_bounds(bounds), m_callback(std::move(cb))
{
	InputManager::Get().m_broadcaster->AddListener(
		this->AddComponent<MouseListenerComponent>([this](const MSG& msg) {
		this->Worked(msg); }));
    
	//Object�� position, size;width & height ���� 
	SetPosition({ m_bounds.left, m_bounds.top }, {m_bounds.right- m_bounds.left, m_bounds.top-m_bounds.bottom});

}

Button::~Button() //��� ������Ʈ�� ����ǵ� 
{
	m_callback = nullptr;
	
}

void Button::Worked(const MSG& msg) //������ Ŭ���� ������, ���߿��� ���콺 Ŀ�� �ø��� ��������Ʈ �����ϴ� �ڵ嵵 �߰� ���� 
{
    if (InputManager::Get().IsInCallback()) return;

    if (!m_enabled || already_Done || msg.message != WM_LBUTTONDOWN)
        return;



    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };

    std::cout << "X���콺��" << CORD.x << "y���콺��" << CORD.y << endl;


    if (PtInRect(&m_bounds, CORD) && !already_Done)
    {
        already_Done = true;
        m_enabled = false;

        if (m_callback) {
            InputManager::Get().SetInCallback(true);
            m_callback(msg);
            InputManager::Get().SetInCallback(false);
        }
    }
}

