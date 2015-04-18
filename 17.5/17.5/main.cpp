#undef UNICODE
#include<algorithm>
#include <windows.h>
#include<atltypes.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
HWND hwnd;

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Светофор";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG msg;
  /*хотя параметр hPrevInstance в Win32 всегда равно NULLпродолжаем проверять его значение */
  if (!hPrevInstance) 
  {  /* инициализируем приложение -  подготавливаем данные класса окна и регистрируем его */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }
   /* завершаем создание копии приложения -     создаем главное окно приложения */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);  
  
  /* Цикл обработки сообщений */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  // Заполняем структуру класса окна WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE +0);
  wc.lpszMenuName  = szTitle;
  wc.lpszClassName = szClassName;
  // Регистрируем класс окна
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  
  hwnd = CreateWindow(
    szClassName,         // указатель на строку зарегистрированного имени класса
    szTitle,             // указатель на строку заголовка окна
    WS_OVERLAPPEDWINDOW, // стиль окна
    CW_USEDEFAULT,       // горизонтальная координата окна
    CW_USEDEFAULT,       // вертикальная координата окна
    CW_USEDEFAULT,       // ширина окна
    CW_USEDEFAULT,       // высота окна
    NULL,                // дескриптор родительского окна
    NULL,                // дескриптор меню окна
    hInstance,           // дескриптор экземпляра приложения
    NULL);               // указатель на дополнительные данные окна

  if (!hwnd)    return (FALSE); 
  //HACCEL hAccel=LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
  return (TRUE);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{  
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	static int r1=255,g1=255,b1=255,r2=255,r3=255,g2=255,g3=255,b2=255,b3=255;
	static int circle=0;
	switch(message)
	{ 
	case WM_CREATE:
		SetTimer(hwnd, 1,1000,NULL);
		return 0;
	case WM_TIMER:
		if(circle<1)
		{
			r1=255; g1=0; b1=0; 
			r2=255; b2=255; g2=255; 
			r3=255; g3=255; b3=255; 
		}
		if((circle>=1 )&&(circle<2))
		{ 
			r2=255; g2=255; b2=0; 
			r1=255; g1=255; b1=255; 
			r3=255; g3=255; b3=255;
		};		
		if((circle>=2) &&(circle<3))
		{
			r3=0; g3=255; b3=0; 
			r1=255; g1=255; b1=255; 
			r2=255; g2=255; b2=255;
		}
		if(circle>=3) 
			circle=-1;
		hDC=GetDC(hwnd);
		GetClientRect(hwnd,&rect);
		circle++;
		InvalidateRect(hwnd,&rect,true);
		break;	
    case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd,&rect);
		HBRUSH hBrush;
		hBrush=CreateSolidBrush(RGB(127,255,212));
		SelectObject(hDC,hBrush);
		Rectangle(hDC,rect.right/2-100, rect.bottom/2-200,rect.right/2+100,rect.bottom/2+200);
		hBrush=CreateSolidBrush(RGB(r1,g1,b1));
		SelectObject(hDC,hBrush);
		Ellipse(hDC,rect.right/2-60, rect.bottom/2-175, rect.right/2+60, rect.bottom/2-75);
		hBrush=CreateSolidBrush(RGB(r2,g2,b2));
		SelectObject(hDC,hBrush);
		Ellipse(hDC,rect.right/2-60, rect.bottom/2-55, rect.right/2+60, rect.bottom/2+45);
		hBrush=CreateSolidBrush(RGB(r3,g3,b3));
		SelectObject(hDC,hBrush);
		Ellipse(hDC,rect.right/2-60, rect.bottom/2+65, rect.right/2+60, rect.bottom/2+165);
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