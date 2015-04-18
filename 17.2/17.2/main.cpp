#undef UNICODE
#include<algorithm>
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "�������� ���� Windows";
HWND hWnd;

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
  // ��������� ��������� ������ ���� WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE-0);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
  // ������������ ����� ����
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
	int size;
	switch(message)
	{
    case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		HBRUSH hBrush;
		hBrush=CreateSolidBrush(RGB(230 ,230, 250));
		SelectObject(hDC,hBrush);
		GetClientRect(hwnd,&rect);
		size=rect.right/4;
		MoveToEx(hDC,rect.right/4,0,NULL);
		LineTo(hDC,rect.right/4,rect.bottom);
		MoveToEx(hDC,rect.right/2,0,NULL);
		LineTo(hDC,rect.right/2,rect.bottom);
		MoveToEx(hDC,3*rect.right/4,0,NULL);
		LineTo(hDC,3*rect.right/4,rect.bottom);
		Rectangle(hDC,rect.right/4+10,10,rect.right/2-10,rect.bottom/4);
		TextOut(hDC,rect.right/4+10,rect.bottom/4+10,"Rectangle",9);
		POINT T[4];
		T[0].x=3*rect.right/4+10; 
		T[0].y=size/2+10;
		T[1].x=3*rect.right/4+size/2; 
		T[1].y=10;
		T[2].x=rect.right-10; 
		T[2].y=size/2+10;
		T[3].x=3*rect.right/4+size/2;
		T[3].y=size+10;
		Polygon(hDC, T, 4);
		hBrush=CreateSolidBrush(RGB(255 ,228, 225));
		SelectObject(hDC,hBrush);
		Ellipse(hDC,10,10,rect.right/4-10,rect.bottom/4);
		TextOut(hDC,10,rect.bottom/4+10,"Ellipse", 7);  
 		Pie(hDC,rect.right/2+10,10, 3*rect.right/4-10,size-10,5*rect.right/8,10,5*rect.right/8-((size/2)-10)/2,10+(size/2-10)*(1-sqrt(3.00)/2));
		TextOut(hDC,rect.right/2+10,rect.bottom/4+10,"Sector", 6);
		/* MoveToEx(hDC,3*rect.right/4+10,size/2+10,NULL);
	  	LineTo(hDC,3*rect.right/4+size/2,10);
		LineTo(hDC,rect.right-10,size/2+10);
		LineTo(hDC,3*rect.right/4+size/2,n+10);
		LineTo(hDC,3*rect.right/4+10,size/2+10);*/
		TextOut(hDC,3*rect.right/4+10,rect.bottom/4+size/2+10,"Romb",4 );
		EndPaint(hwnd, &ps);
		break;
    case WM_DESTROY:
		PostQuitMessage(0);
		break;
    default:
		return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
}