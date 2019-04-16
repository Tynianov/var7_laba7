#include "Header.h"
#define ID_BUTTON1 0x320
// �������� ����:
HINSTANCE hInst; 	//���������� ��������	
LPCTSTR szWindowClass = "LAB7";
LPCTSTR szTitle = "LAB7";
static char file_name[200];
static OPENFILENAME ofn;

// ��������� ���� �������
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// ������� �������� 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// ��������� ����� ���� 
	MyRegisterClass(hInstance);

	// ��������� ���� ��������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// ���� ������� ����������
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
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//����� ����
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//������ ���������
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//���������� ��������
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); 		//���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//���������� �������
	wcex.hbrBackground = GetSysColorBrush(WHITE_BRUSH); //��������� ����
	wcex.lpszMenuName = NULL; 				//���������� ����
	wcex.lpszClassName = szWindowClass; 		//��� �����
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//��������� ����� ����
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
// ������� ���� �������� � ������ ���������� �������� � ����� hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //������ ���������� ������� � ����� hInst
	hWnd = CreateWindow(szWindowClass, 	// ��� ����� ����
		szTitle, 				// ����� ��������
		WS_OVERLAPPEDWINDOW,			// ����� ����
		CW_USEDEFAULT, 			// ��������� �� �	
		CW_USEDEFAULT,			// ��������� �� Y	
		400, 			// ����� �� �
		550, 			// ����� �� Y
		NULL, 					// ���������� ������������ ����	
		NULL, 					// ���������� ���� ����
		hInstance, 				// ���������� ��������
		NULL); 				// ��������� ���������.

	InitOpenDialog(hWnd);
	if (!hWnd) 	//���� ���� �� ���������, ������� ������� FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//�������� ����
	UpdateWindow(hWnd); 				//������� ����
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// ³����� ���������. ������ � �������� �� �����������, �� ��������� � �������


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND edit[3];
	ReadData * my_data;

	switch (message)
	{
	case WM_CREATE: 				//����������� ��������� ��� �������� ��-��
		edit[0] = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD, 150, 10, 200, 18, hWnd, NULL, GetModuleHandle(NULL), NULL);
		edit[1] = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD, 150, 40, 200, 18, hWnd, NULL, GetModuleHandle(NULL), NULL);
		edit[2] = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | EN_VSCROLL, 150, 70, 200, 400, hWnd, NULL, GetModuleHandle(NULL), NULL);

		CreateWindow("button", "������", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 35, 100, 25, hWnd, (HMENU)ID_BUTTON1, GetModuleHandle(NULL), NULL);
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

	case WM_DESTROY: 				//���������� ������
		PostQuitMessage(0);
		break;
	default:
		//������� ����������, �� �� �������� ������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}