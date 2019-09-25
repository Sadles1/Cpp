#include <Windows.h>
#include <ctime>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>


int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	srand(time(NULL));
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	wc.hbrBackground = hBrush;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;

	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg)
		{
			case WM_LBUTTONDOWN:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				RECT rect;
				GetWindowRect(hWnd, &rect);
				LONG Width = rect.right - rect.left;//Ширина окна
				LONG Height = rect.bottom - rect.top;//Высота окна


				if (x > Width / 2 && y > Height / 2)//Правый нижний угол
				{
					InvalidateRect(hWnd, NULL, TRUE);
					SetClassLongPtr(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 255)));//синий
				}
				if (x > Width / 2 && y < Height / 2)//Левый верхний угол
				{
					InvalidateRect(hWnd, NULL, TRUE);
					SetClassLongPtr(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 0)));//жёлтый
				}
				if (x < Width / 2 && y < Height / 2)//Правый верхний угол
				{
					InvalidateRect(hWnd, NULL, TRUE);
					SetClassLongPtr(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 0, 0)));//Красный
				}
				if (x < Width / 2 && y > Height / 2)//Левый нижний угол
				{
					InvalidateRect(hWnd, NULL, TRUE);
					SetClassLongPtr(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 255, 0)));//зелённый
				}
			}
			break;
			case WM_DESTROY:
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
			case WM_KEYDOWN:
			{
				if ((wParam == 'Q' && GetAsyncKeyState(VK_CONTROL)) || (wParam == 27))//Выключение программы по нажатию esc или ctrl+q
				{
					ExitProcess(1);
				}
				if (LOWORD(wParam) == 'C' && GetAsyncKeyState(VK_SHIFT))//Запуск блокнота по нажатию shift
				{
					STARTUPINFO sInfo;
					ZeroMemory(&sInfo, sizeof(STARTUPINFO));
					PROCESS_INFORMATION pInfo;
					CreateProcess("C:\\Windows\\Notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &sInfo, &pInfo);
				}
				if (wParam == 13)//Изменение цвета по нажатию enter
				{
					InvalidateRect(hWnd, NULL, TRUE);
					SetClassLongPtr(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
				}
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};

	wc.lpszClassName = "MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

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
