#include <windows.h>
#include "WindowsMessageMap.h"

#include <stdio.h>
#include <TCHAR.h>


LRESULT CALLBACK WinProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	static WindowsMessageMap mm;
	OutputDebugString( mm(uMsg, lParam, wParam).c_str());


	switch (uMsg)
	{
	case WM_CHAR:
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_PAINT:
		break;
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	//���һ��������
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndcls.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WinProc;
	wndcls.lpszClassName = "csdn";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	//�������ڣ�����һ��������������ɹ��������ں󷵻صľ��
	HWND hwnd;
	hwnd = CreateWindow("csdn", "www.csdn.net", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);

	//��ʾ��ˢ�´���
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//������Ϣ�ṹ�壬��ʼ��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

