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
    //m_transform�� ��ǥ�� �������� ���� �Ѱ��� 
}

Button::~Button() //��� ������Ʈ�� ����ǵ� 
{
	m_callback = nullptr;
	
}

void Button::Worked(const MSG& msg) //������ Ŭ���� ������, ���߿��� ���콺 Ŀ�� �ø��� ��������Ʈ �����ϴ� �ڵ嵵 �߰� ���� 
{
    if ( msg.message != WM_LBUTTONDOWN)
        return;

    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };



    if (PtInRect(&m_bounds, CORD)) //��ġ�� �����Ǿ����ϱ� 
    {
        
        m_callback(msg);
           
    }
}

