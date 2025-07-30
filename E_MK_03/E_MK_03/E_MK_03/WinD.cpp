#include "pch.h"
#include "WinD.h"

LRESULT NzWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
{
	switch (msg) //�⺻���� wnd eventó���� �ϰ� ��. msg->Inputó���� RUN���� ���� �̷����(Ȯ�强 ����) 
	{
	case WM_SIZING:
	{
		RECT* rect = (RECT*)lparam;

		RECT rc = { 0, 0, 1920, 1080 };
		AdjustWindowRect(&rc, GetWindowLong(hwnd, GWL_STYLE), FALSE);

		int frameWidth = rc.right - rc.left;
		int frameHeight = rc.bottom - rc.top;

		rect->right = rect->left + frameWidth;
		rect->bottom = rect->top + frameHeight;
		return TRUE;
		//RECT* rect = (RECT*)lparam;

		//const int Width = 1920;
		//const int Height = 1080;

		//rect->right = rect->left + Width;
		//rect->bottom = rect->top + Height;

		//break;
	}
	

	case WM_DESTROY:
		std::cout << "WM_DESTROY received, exiting..." << std::endl;
		PostQuitMessage(0);
		break;


	default:
		return::DefWindowProc(hwnd, msg , wparam, lparam);
	}//switch

	return NULL;
}

bool WinD::Create(const wchar_t* className, const wchar_t* windowName, int width, int height)
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = className;
	wc.lpfnWndProc = NzWndProc; //���ν��� ��� 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // �� ���� ��Ÿ�� �߰�


	ATOM classId = 0;
	if (!GetClassInfoEx(HINSTANCE(), className, &wc))
	{
		classId = RegisterClassEx(&wc);

		if (0 == classId) return false;
	}

	m_width = width;
	m_height = height;

	RECT rc = { 0, 0, width, height };
	//������ â ���� ��, ������ �ִ� ��. 
	AdjustWindowRect(&rc,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	m_hWnd = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, HWND(), HMENU(), HINSTANCE(), NULL);

	if (NULL == m_hWnd) return false;

	::SetWindowText((HWND)m_hWnd, windowName);
	SetWindowLongPtr((HWND)m_hWnd, GWLP_USERDATA, (LONG_PTR)this); 
	//WinD�� �ڽ� ��ü�� Core�� ����Ű�� Pointer-> �̺�Ʈ ��� �Լ��� �ش� ������ ��ü���� ����

	ShowWindow((HWND)m_hWnd, SW_SHOW);
	UpdateWindow((HWND)m_hWnd);

	return true;
}

void WinD::Delete()
{
	if (NULL != m_hWnd)
	{
		DestroyWindow((HWND)m_hWnd);
		m_hWnd = NULL;
	}
}
