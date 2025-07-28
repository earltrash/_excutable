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
    
	//Object에 position, size;width & height 저장 
	SetPosition({ m_bounds.left, m_bounds.top }, {m_bounds.right- m_bounds.left, m_bounds.top-m_bounds.bottom});

}

Button::~Button() //모든 컴포넌트를 지울건데 
{
	m_callback = nullptr;
	
}

void Button::Worked(const MSG& msg) //지금은 클릭만 하지만, 나중에는 마우스 커서 올리면 스프라이트 변경하는 코드도 추가 가능 
{
    if (InputManager::Get().IsInCallback()) return;

    if (!m_enabled || already_Done || msg.message != WM_LBUTTONDOWN)
        return;



    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };

    std::cout << "X마우스값" << CORD.x << "y마우스값" << CORD.y << endl;


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

