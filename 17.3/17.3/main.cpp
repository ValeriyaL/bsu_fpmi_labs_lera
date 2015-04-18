#undef UNICODE
#include<algorithm>
#include <windows.h>
#include<atltypes.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Text";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
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
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
//   ��������� ��������� ������ ���� WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE +0);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
//   ������������ ����� ����
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
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

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);
  return (TRUE);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	int index;
	static int size=20;
	static char mas[100]="Text";
	static HFONT hfont;
	static HFONT hOldFont;
	static LOGFONT lf1;
	lf1.lfHeight = 40; 
    lf1.lfWeight = FW_BOLD; 
	lf1.lfCharSet = RUSSIAN_CHARSET; 
	lf1.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN; 	  
	switch(message)
	{ 
    case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd,&rect);
		SelectObject(hDC, hfont);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC,mas,-1,&rect,DT_VCENTER | DT_SINGLELINE |DT_CENTER );
		EndPaint(hwnd, &ps);
		break;
    case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:  
		GetClientRect(hwnd,&rect);
		switch(wParam)
		{
		case '+' :	     
			index=strlen(mas);
			mas[index]='+';
			size+=5;
			lf1.lfHeight=size;
			hfont=CreateFontIndirect(&lf1);
			InvalidateRect(hwnd,&rect,true);
			break;
		case '-' : 
			index=strlen(mas);
			mas[index]='-';
			size-=5;
			lf1.lfHeight=size;
			hfont=CreateFontIndirect(&lf1);
			InvalidateRect(hwnd,NULL,true);
			break;
			}
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
}