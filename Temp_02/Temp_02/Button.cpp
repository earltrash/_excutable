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
	SetPosition({ m_bounds.left, m_bounds.top });
    //m_transform에 좌표계 기준으로 값을 넘겨줌 

     activated = true; //이게 좀 어렵구만, 가장 상위 계층 만들 때 고민해 봐야 할듯 

}

Button::~Button() //모든 컴포넌트를 지울건데 
{
	m_callback = nullptr;
	
}

void Button::Worked(const MSG& msg) //지금은 클릭만 하지만, 나중에는 마우스 커서 올리면 스프라이트 변경하는 코드도 추가 가능 
{
    if (!activated)  //이것도 분기 나눠서, 커서 올리기랑 클릭을 분리해야 함!!! 
        return; 

    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };

    if (PtInRect(&m_bounds, CORD))
    {
        if (msg.message == WM_LBUTTONDOWN)
        {
            m_callback(msg);
        }
        else if (msg.message == WM_MOUSEMOVE)
        {
            //뭐 외형 바꾸는 거라도 하지 않을깝쇼...
        }



    }
        
        
           
    
}

