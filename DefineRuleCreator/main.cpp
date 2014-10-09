#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <fstream>

#include "tinyxml2.h"
#include "HexagonGenerator.h"

#define ACCEPT_RULE_BUTTON 101
#define ACCEPT_CELLTYPE_BUTTON 102

HWND hAcceptRuleButton;
HWND hAcceptCellTypeButton;
int windowWidth = 500;
int windowHeight = 500;

static HexagonGenerator* hc;

void GenerateCellType()
{
	std::ofstream file;
	file.open("../Define/files/CellTypes.txt", std::ios_base::app | std::ofstream::out);
	if (!file)
	{
		cout << "whoops";
	}
	
	string newRule = hc->GenerateCellType();
	file << newRule;
	file.close();
}

void ActivateConsole()
{
	FILE *conin, *conout;
	AllocConsole();
	freopen_s(&conin, "conin$", "r", stdin);
	freopen_s(&conout, "conout$", "w", stdout);
	freopen_s(&conout, "conout$", "w", stderr);
}

//LPCWSTR szWindowClass = L"test";
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT wind;
	POINT mouse;
	switch(message)
	{
	case WM_CREATE:
		hAcceptRuleButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Accept Rule",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 80, 30, hWnd, (HMENU)ACCEPT_RULE_BUTTON,
			GetModuleHandle(NULL), NULL);
		hAcceptCellTypeButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Accept Cell Type",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 90, 80, 30, hWnd, (HMENU)ACCEPT_CELLTYPE_BUTTON,
			GetModuleHandle(NULL), NULL);
		break;
	case WM_COMMAND:
		switch LOWORD(wParam) //the ID is is wParam
		{
			case ACCEPT_CELLTYPE_BUTTON: //check for our button ID
			{
				// Static labels dont do messages
				//we can set the text directly though
				GenerateCellType();
				break;
			}
			case ACCEPT_RULE_BUTTON:
			{
				hc->SaveRule();
				break;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		GetCursorPos(&mouse);
		ScreenToClient(hWnd, &mouse);
		wind = hc->CycleClickedHexagon(mouse);
		InvalidateRect(hWnd,&wind, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetCursorPos(&mouse);
		ScreenToClient(hWnd, &mouse);
		SetPixel(hdc, mouse.x, mouse.y, RGB(255, 55, 5));
		hc->DrawHexagons(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	static TCHAR szWindowClass[] = _T("Test");
	static TCHAR szTitle[] = _T("Win32 tour");
	
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("RegisterClassEx failed"), _T("Win32 Guided Tour"), NULL);
		
		return 1;
	}
	
	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	ActivateConsole();

	hc = new HexagonGenerator;
	hc->GenerateHexagons(500, 500, 25, 1);

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	delete hc;
	return (int)msg.wParam;
}



