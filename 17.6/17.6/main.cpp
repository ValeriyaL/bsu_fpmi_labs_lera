#undef UNICODE
#include<algorithm>
#include <windows.h>
#include <string> 
#include <sstream>
#include <stdlib.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "�������� ���� Windows";
HWND hwnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	/*���� �������� hPrevInstance � Win32 ������ ����� NULL���������� ��������� ��� �������� */
	if (!hPrevInstance)
	{  /* �������������� ���������� -  �������������� ������ ������ ���� � ������������ ��� */
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	/* ��������� �������� ����� ���������� -     ������� ������� ���� ���������� */
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	/* ���� ��������� ��������� */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 0);
	wc.lpszMenuName = NULL;// MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = szClassName;
	// ������������ ����� ����
	return RegisterClass(&wc);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hwnd = CreateWindow(
		szClassName,         // ��������� �� ������ ������������������� ����� ������
		szTitle,             // ��������� �� ������ ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT,       // �������������� ���������� ����
		CW_USEDEFAULT,       // ������������ ���������� ����
		CW_USEDEFAULT,       // ������ ����
		CW_USEDEFAULT,       // ������ ����
		NULL,                // ���������� ������������� ����
		NULL,                // ���������� ���� ����
		hInstance,           // ���������� ���������� ����������
		NULL);               // ��������� �� �������������� ������ ����

	if (!hwnd)    return (FALSE);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam)
{
	HDC hDC; 
	static RECT rect; 
	HPEN hpen;  
	static int x0; 
	static int x1, y1; 
	static float koord;
	PAINTSTRUCT ps; 
	switch (message)
	{	
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		x0 = rect.right / 30;
		MoveToEx(hDC,3*x0,rect.bottom/2,NULL);
		LineTo(hDC, rect.right - 3 * x0, rect.bottom / 2);
		LineTo(hDC, rect.right - 3 * x0-25, rect.bottom / 2-5);
		MoveToEx(hDC, rect.right - 3 * x0, rect.bottom / 2,NULL);
		LineTo(hDC, rect.right - 3 * x0 - 25, rect.bottom / 2 + 5);
		MoveToEx(hDC, rect.right/2,2*x0, NULL);
		LineTo(hDC, rect.right/2,rect.bottom -2*x0);
		MoveToEx(hDC, rect.right / 2, 2 * x0, NULL);
		LineTo(hDC, rect.right / 2+5, 2 * x0+25);
		MoveToEx(hDC, rect.right / 2, 2 * x0, NULL);
		LineTo(hDC, rect.right / 2 - 5, 2 * x0 + 25);
		MoveToEx(hDC, rect.right/2,rect.bottom/2,NULL);
		int x, y; 
		static char arr[3]; 
		hpen = CreatePen(PS_DASH, 3, RGB(0, 0, 255));
		SelectObject(hDC, hpen);
		for (int i = -5 ; i <6; i ++)
		{
			x = rect.right / 2 + x0*i;
			y = rect.bottom/2-x0*i;
			LineTo(hDC,x,y);
			_itoa_s(i, arr, 10);
			SetBkMode(hDC, TRANSPARENT);
			TextOut(hDC, x, rect.bottom / 2+6, arr, 2);
			if (i!=0)
			TextOut(hDC, rect.right/2-16, y, arr, 2);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		hDC = GetDC(hwnd);
		x1 = LOWORD(lparam);
		y1 = HIWORD(lparam);
		if (GetPixel(hDC,x1,y1)==RGB(0,0,255))
		{	
			koord =(float) (x1 - rect.right / 2.00) / x0;
			static char arr[10];
			sprintf_s(arr, "%f", koord);
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(255, 0, 0));
			TextOut(hDC, x1, rect.bottom / 2 - 3, arr , 4);
			TextOut(hDC, rect.right / 2 + 3, y1, arr, 4);
			hpen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
			SelectObject(hDC,hpen);
			MoveToEx(hDC, x1, rect.bottom / 2,NULL);
			LineTo(hDC,x1,y1);
			MoveToEx(hDC, rect.right/2, y1, NULL);
			LineTo(hDC, x1, y1);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lparam);
	}
	return 0;
}
