#include "Header.h"
#define ID_BUTTON1 0x320
// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "LAB7";
LPCTSTR szTitle = "LAB7";
static char file_name[200];
static OPENFILENAME ofn;

// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(WHITE_BRUSH); //установка фону
	wcex.lpszMenuName = NULL; 				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

BOOL InitOpenDialog(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.nMaxFile = sizeof(file_name);
	ofn.lpstrFilter = "Text file(.txt)\0 * .txt\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return TRUE;
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_OVERLAPPEDWINDOW,			// стиль вікна
		CW_USEDEFAULT, 			// положення по Х	
		CW_USEDEFAULT,			// положення по Y	
		400, 			// розмір по Х
		550, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	InitOpenDialog(hWnd);
	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND edit[3];
	ReadData * my_data;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вік-на
		edit[0] = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD, 150, 10, 200, 18, hWnd, NULL, GetModuleHandle(NULL), NULL);
		edit[1] = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD, 150, 40, 200, 18, hWnd, NULL, GetModuleHandle(NULL), NULL);
		edit[2] = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | EN_VSCROLL, 150, 70, 200, 400, hWnd, NULL, GetModuleHandle(NULL), NULL);

		CreateWindow("button", "Кнопка", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 35, 100, 25, hWnd, (HMENU)ID_BUTTON1, GetModuleHandle(NULL), NULL);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_BUTTON1:
			GetOpenFileName(&ofn);
			my_data = readFromFile(ofn);
			display(my_data, edit);
			delete my_data;
			break;
		}
		break;

	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}