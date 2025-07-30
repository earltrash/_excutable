#include "Potion.h"



Potion::Potion(const ItemCommonData& data, const json& j) : Item(data)
{
    if (j.contains("much"))
        much = j["much"];

    else cout << "�� ������ �� �� ���µ���?" << endl;
}

void Potion::Worked(const MSG& msg)
{
    if (!activated)
        return;

    POINT CORD = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };


    // return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

    if (PtInRect(&m_bounds, CORD)) //Item ���� ��쿡�� ��ǥ���� ������ ��ȿ�� �� �ٰ� �ƴ� 
    {
        switch (msg.message)
        {
        case WM_LBUTTONDBLCLK: //���� Ŭ��
        {
            //���� �Լ� ���� ��Ű�� 
        }
        break;

        case WM_MOUSEMOVE:
        {
            if (isDragging)
            {
                POINT current = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
                //������Ʈ�� m_transform�� ���� current������ ���� ���Ѿ� ��. 
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
