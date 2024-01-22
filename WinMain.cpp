#include <windows.h>
#include "WindowsMessageMap.h"

#include <stdio.h>
#include <TCHAR.h>

#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//static WindowsMessageMap mm;//����msg������
	//OutputDebugString(mm(msg, lparam, wparam).c_str());//���������Ϣ���з��룬���Կ���wparam��lparam����
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN://���̰����Ƿ���
		if (wparam == 'F');//�Ƿ���F��
		{
			SetWindowText(hwnd, "keydown");//�����ڱ�������Ϊkeydown
		}
		break;
	case WM_KEYUP://�����ɿ�����Ϣ
		if (wparam == 'F');
		{
			SetWindowText(hwnd, "keyup");
		}
		break;
	case WM_CHAR://���ݴ���
	{
		static std::string title;
		title.push_back((char)wparam);
		SetWindowText(hwnd, title.c_str());
		break;
	}

	case WM_LBUTTONDOWN://����������
	{
		const POINTS pt = MAKEPOINTS(lparam);//32λ���и�16λ�͵�16λ��ϳ�����λ�ã�ÿ��msg������Ϣ��ͬ��������֮���������
		std::ostringstream otsting;
		otsting << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hwnd, otsting.str().c_str());//��������ΪĿǰ��������
		break;
	}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
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
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = "XDXCT";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	//�������ڣ�����һ��������������ɹ��������ں󷵻صľ��
	HWND hwnd;
	hwnd = CreateWindow("XDXCT", "www.xdxct.com", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);

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

