#include "Potion.h"



Potion::Potion(const ItemCommonData& data, const json& j) : Item(data)
{
    if (j.contains("much"))
        much = j["much"];

    else cout << "얘 가져야 할 게 없는데요?" << endl;
}

void Potion::Worked(const MSG& msg)
{
    if (!activated)
        return;

    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };


    // return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

    if (PtInRect(&m_bounds, CORD)) //Item 같은 경우에는 좌표값이 영역에 유효한 게 다가 아님 
    {
        switch (msg.message)
        {
        case WM_LBUTTONDBLCLK: //더블 클릭
        {
            //물약 함수 실행 시키기 
        }
        break;

        case WM_MOUSEMOVE:
        {
            if (isDragging)
            {
                POINT current = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
                //오브젝트의 m_transform을 현재 current값으로 변경 시켜야 함. 
               // m_transform.SetPosition()
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {
            isDragging = true;
        }
        break;
        case WM_LBUTTONUP:
        {
            isDragging = false;
            break;
        }
        default:
            break;
        }
    }
}
