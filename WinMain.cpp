#include <windows.h>
#include "WindowsMessageMap.h"

#include <stdio.h>
#include <TCHAR.h>

#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//static WindowsMessageMap mm;//调用msg翻译类
	//OutputDebugString(mm(msg, lparam, wparam).c_str());//将传入的信息进行翻译，可以看到wparam和lparam数据
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN://键盘按键是否按下
		if (wparam == 'F');//是否是F键
		{
			SetWindowText(hwnd, "keydown");//将窗口标题设置为keydown
		}
		break;
	case WM_KEYUP://按键松开的消息
		if (wparam == 'F');
		{
			SetWindowText(hwnd, "keyup");
		}
		break;
	case WM_CHAR://数据传入
	{
		static std::string title;
		title.push_back((char)wparam);
		SetWindowText(hwnd, title.c_str());
		break;
	}

	case WM_LBUTTONDOWN://鼠标左键按下
	{
		const POINTS pt = MAKEPOINTS(lparam);//32位其中高16位和低16位组合成坐标位置，每个msg代表信息不同，因此输出之后更加清晰
		std::ostringstream otsting;
		otsting << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hwnd, otsting.str().c_str());//标题设置为目前鼠标的坐标
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
	//设计一个窗口类
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

	//创建窗口，定义一个变量用来保存成功创建窗口后返回的句柄
	HWND hwnd;
	hwnd = CreateWindow("XDXCT", "www.xdxct.com", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);

	//显示及刷新窗口
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//定义消息结构体，开始消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

