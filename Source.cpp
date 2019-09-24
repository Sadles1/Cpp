#include <Windows.h>
#include <ctime>
#include <windowsx.h>
#define HOTKEX 1
int x;
int	y;

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)//точка входа
{
	MSG msg{};
	HWND hwnd{}; //Инфромация о окне
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0; //Дополнительное выделение памяти
	wc.cbWndExtra = 0;
	srand(time(NULL));
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	wc.hbrBackground = hBrush;//Окрас окна
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);//Курсор
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);//Иконка
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);//Иконка в заголовке окна
	wc.hInstance = hInstance;

	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT//обработка сообщений
	{
		switch (uMsg)
		{
			case WM_LBUTTONDOWN:
			{
				if (hWnd)
				{
					x = LOWORD(lParam);
					y = HIWORD(lParam);
				}
			}
			break;
			case WM_CREATE:
			{
				RegisterHotKey(hWnd, HOTKEX, MOD_CONTROL, VK_F12);
			}
			return 0;
			case WM_DESTROY://сообщение в случае выхода
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
			case WM_KEYUP:
			{
				if (wParam == 27)
					ExitProcess(1);
			}
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				if (wParam == 13)
				{
					
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
					EndPaint(hWnd, &ps);
				}
				if (x > 180 && y > 120)//Правый нижний угол
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 0, 255)));//синий
					EndPaint(hWnd, &ps);
				}
				if (x > 180 && y < 120)//Правый верхний угол
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 247, 13)));//жёлтый
					EndPaint(hWnd, &ps);
				}
				if ( x>0 && x < 180 && y < 120 && y >0)//Левый верхний угол
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 0, 0)));//красный
					EndPaint(hWnd, &ps);
				}
				if (x < 180 && y > 120)//Левый нижний угол
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 255, 26)));//зелёный
					EndPaint(hWnd, &ps);
				}
			}
			return 0;
			/*
			case WM_HOTKEY:
			{
				if (HOTKEX == (int)wParam)
				{
					MessageBoxA(hWnd, "Hi", "Info", MB_OK);

				}
			}
			break;
			case WM_KEYDOWN:
			{
				if (LOWORD(wParam) == 51 && HIWORD(lParam) == 4)  // Ctrl+3(левый контрол) Необходимо переделать на Ctrl+ Q
					ExitProcess(1);
				/*if ();
					STARTUPINFO sInfo;
					ZeroMemory(&sInfo, sizeof(STARTUPINFO));

					PROCESS_INFORMATION pInfo;
					CreateProcess("C:\\Windows\\Notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &sInfo, &pInfo);
				
			}
			*/
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};

	wc.lpszClassName = "MyAppClass";//Имя класса
	wc.lpszMenuName = nullptr;//идентификатор меню
	wc.style = CS_VREDRAW | CS_HREDRAW;//Стиль Окна

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;
	
	hwnd = CreateWindow(wc.lpszClassName, "Селедков Виталий БАС-2018", WS_OVERLAPPEDWINDOW, 0, 0, 320, 240, nullptr, nullptr, wc.hInstance, nullptr);

	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return static_cast<int>(msg.wParam);
}