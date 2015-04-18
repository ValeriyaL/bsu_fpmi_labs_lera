#undef UNICODE

#include <windows.h>
#include<vector>
#include<algorithm>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "ClassName";

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{	
HWND hWnd;
	MSG msg;
	WNDCLASS wcApp;

	// Заполняем структуру класса окна 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance		= hInstance;   
	wcApp.lpfnWndProc	= WndProc;
	wcApp.hCursor		= LoadCursor(NULL,IDC_HELP);
	wcApp.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName	= 0;
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style			= CS_HREDRAW | CS_VREDRAW;
	wcApp.cbClsExtra	= 0;
	wcApp.cbWndExtra	= 0;
	
// Регистрируем класс окна
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hWnd=CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	/*ShowWindow(hWnd,nCmdShow);*/
	ShowWindow(hWnd,SW_MINIMIZE);
	UpdateWindow(hWnd);

	while (GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_PAINT:{
		hdc=BeginPaint(hWnd,&ps);
		// drawing code
		RECT rect;
		GetClientRect(hWnd, &rect);
		Rectangle(hdc, 10, 20, rect.right -10, rect.bottom -20);
		Ellipse(hdc,rect.left+10, rect.top+20, rect.right-10, rect.bottom-20);
		TextOut(hdc,0,0,"Text", 4);
		TextOut(hdc,rect.right-30,0,"Text", 4);
		TextOut(hdc,0,rect.bottom-15,"Text", 4);
		TextOut(hdc,rect.right-30,rect.bottom-15,"Text", 4);
		DrawText(hdc,"Text", 5, &rect,DT_SINGLELINE| DT_CENTER | DT_VCENTER);
		EndPaint(hWnd,&ps);}
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd,uMsg,wParam,lParam));
	}
	return (0);
}
