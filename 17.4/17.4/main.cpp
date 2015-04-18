#undef UNICODE
#include<algorithm>
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Таймер";
HWND hWnd;

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
  wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE-0);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
  // Регистрируем класс окна
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
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

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);
  return (TRUE);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam)
{  
    HDC hdc; 
	RECT rect; 
	static char arr[10];
    PAINTSTRUCT ps; 
	static int sec=0; 
	static bool pause=false;  
	static int key;
	HFONT hfont;
	static LOGFONT lf;
	lf.lfHeight = 40;
	lf.lfWeight = FW_MEDIUM; 
	lf.lfCharSet = RUSSIAN_CHARSET; 
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;  
    switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd,1,1000,NULL);
	case WM_TIMER:
		if(!pause)
		{
			sec++;	
			itoa(sec,arr,10);	
			InvalidateRect(hwnd, NULL, false); 
		}
		break;
	case WM_PAINT : 
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd,&rect);
		Ellipse(hdc,rect.right/2-100,rect.bottom/2-100,rect.right/2+100,rect.bottom/2+100);
		hfont=CreateFontIndirect(&lf);
		SelectObject(hdc, hfont);
		DrawText(hdc,arr,-1,&rect,DT_VCENTER | DT_SINGLELINE |DT_CENTER );
		DeleteObject(hfont);
		break;
	case WM_CHAR:
		switch(wParam)
		{	
		case'-' : 
			pause=true;
			break; 
		case '+' :
			pause=false; 
			break;
		}
		break;
	case WM_KEYDOWN:
		key=wParam; 
		switch(key) 
		{	
		case 83: 	
			hdc = GetDC(hwnd);
            key = GetKeyState(VK_SHIFT);
            if (key) 
			{
				pause=false;
				sec=0;
				itoa(sec,arr,10);
				break;
			}
			break;
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