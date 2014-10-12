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
#define SAVE_BUTTON 103
#define ACTION_TYPE_ATTACK_BUTTON 104
#define ACTION_TYPE_MOVE_BUTTON 105
#define DIRECTION_INPUT_BOX 106
#define RGB_INPUT_BOX 107

HWND hAcceptRuleButton;
HWND hAcceptCellTypeButton;
HWND hSaveButton;
HWND hActionTypeMove;
HWND hActionTypeAttack;
HWND hDirectionInputBox;
HWND hRGBInputBox;
int windowWidth = 500;
int windowHeight = 500;
ActionType actionType;

static HexagonGenerator* hc;

void GenerateCellType()
{
	std::ofstream file;
	file.open("../Define/files/CellTypes.txt", std::ios_base::app | std::ofstream::out);
	if (!file)
	{
		cout << "whoops";
	}
	
//	string newRule = hc->GenerateCellType();
//	file << newRule;
	//file.close();
}

void ActivateConsole()
{
	FILE *conin, *conout;
	AllocConsole();
	freopen_s(&conin, "conin$", "r", stdin);
	freopen_s(&conout, "conout$", "w", stdout);
	freopen_s(&conout, "conout$", "w", stderr);
}

void CreateButtons(HWND &hWnd)
{
	hAcceptRuleButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Accept Rule",
		WS_CHILD | WS_VISIBLE | BS_PUSHLIKE, 20, 50, 80, 30, hWnd, (HMENU)ACCEPT_RULE_BUTTON,
		GetModuleHandle(NULL), NULL);
	hAcceptCellTypeButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Accept Cell Type",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 90, 120, 30, hWnd, (HMENU)ACCEPT_CELLTYPE_BUTTON,
		GetModuleHandle(NULL), NULL);
	hSaveButton = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Save",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 130, 80, 30, hWnd, (HMENU)SAVE_BUTTON,
		GetModuleHandle(NULL), NULL);
	hActionTypeMove = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Move",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 20, 80, 30, hWnd, (HMENU)ACTION_TYPE_MOVE_BUTTON,
		GetModuleHandle(NULL), NULL);
	hActionTypeAttack = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Attack",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 20, 80, 30, hWnd, (HMENU)ACTION_TYPE_ATTACK_BUTTON,
		GetModuleHandle(NULL), NULL);
	hDirectionInputBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"D",
		WS_CHILD | WS_VISIBLE | ES_NUMBER, 320, 20, 20, 30, hWnd, (HMENU)DIRECTION_INPUT_BOX,
		GetModuleHandle(NULL), NULL);
	hRGBInputBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"0,0,0",
		WS_CHILD | WS_VISIBLE, 320, 60, 120, 30, hWnd, (HMENU)RGB_INPUT_BOX,
		GetModuleHandle(NULL), NULL);
	
}

int GetDirectionFromInputBox(HWND &hWnd)
{
	return GetDlgItemInt(hWnd, DIRECTION_INPUT_BOX, NULL, NULL);
}

sf::Color GetRGBFromInputBox(HWND& hWnd)
{
	sf::Color result;
	int RGB[3], marker = 0, j = 0;
	int textLength = GetWindowTextLength(hRGBInputBox);
	string temp, text;
	temp.resize(textLength, '\0');
	
	GetWindowTextA(hRGBInputBox, &temp[0], textLength + 1);

	for (int i = 0; i < textLength; ++i)
	{
		if (temp[i] == ',')
		{
			RGB[j] = atoi(text.c_str());
			j++;
			marker = i;
			text = "";
		}
		else
		{
			text += temp[i];
		}
	}
	RGB[j] = atoi(text.c_str());
	result.r = RGB[0];
	result.g = RGB[1];
	result.b = RGB[2];

	return result;
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
		CreateButtons(hWnd);
	case WM_COMMAND:
		switch LOWORD(wParam) //the ID is is wParam
		{
			case ACCEPT_CELLTYPE_BUTTON: //check for our button ID
			{
				// Static labels dont do messages
				//we can set the text directly though
				hc->SaveCellType(GetRGBFromInputBox(hWnd));
				break;
			}
			case ACCEPT_RULE_BUTTON:
			{
				hc->SaveRule(GetDirectionFromInputBox(hWnd), actionType);
				//SendMessage(hAcceptRuleButton, BM_SETSTATE, true, 0);
				//Button_SetCheck(hAcceptRuleButton, BST_CHECKED);
				break;
			}
			case SAVE_BUTTON:
			{
				hc->SaveToXML();
				break;
			}
			case ACTION_TYPE_MOVE_BUTTON:
			{
				actionType = ActionType::Move;
				SendMessage(hActionTypeMove, BM_SETSTATE, true, 0);
				SendMessage(hActionTypeAttack, BM_SETSTATE, false, 0);
				break;
			}
			case ACTION_TYPE_ATTACK_BUTTON:
			{
				actionType = ActionType::Attack;
				SendMessage(hActionTypeMove, BM_SETSTATE, false, 0);
				SendMessage(hActionTypeAttack, BM_SETSTATE, true, 0);
				LPWSTR szInput;

				//GetWindowText(GetDlgItem(hWnd, DIRECTION_INPUT_BOX), szInput, MAX_PATH);
				break;
			}
			case DIRECTION_INPUT_BOX:
			{
//				SendMessage(hDirectionInputBox, WM_SETTEXT, NULL, (LPARAM)"A");
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
	case WM_SETFOCUS:
		cout << "focus" << endl;
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



