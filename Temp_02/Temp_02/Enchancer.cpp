
#include "Enchancer.h"


Enchancer::Enchancer(const ItemCommonData& data, const json& j) : Item(data)
{
    //�ϴ� �̰� �������ӿ� 
    if (j.contains("much"))
        much = j["much"];
    else cout << "�� �־�� �� �� ���µ���?" << endl;

    if (j.contains("stat"))
    {
        string stat = j["stat"];
        which_stat = StringToF(stat);
    }
    else cout << "�� ������ ���о�Ȥ���" << endl;



}

void Enchancer::Worked(const MSG& msg)
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
          
            //��ȭ���� �� ������? //��� ���� 
        }
        break;

        case WM_MOUSEMOVE:
        {
            if (isDragging)
            {
                POINT current = { GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
                //������Ʈ�� m_transform�� ���� current������ ���� ���Ѿ� ��. 
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
            if (isDragging)
            {
                isDragging = false;
               //��ȭ �̺�Ʈ ó���ϱ� 
            }
            break;
        }
        default:
            break;
        }
    }
}
