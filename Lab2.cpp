#include <Windows.h>
#include <ctime>
#include <windowsx.h>
#define HOTKEX 1
int x;
int	y;

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
			case WM_DESTROY:
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
				if (x > 180 && y > 120)
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 0, 255)));
					EndPaint(hWnd, &ps);
				}
				if (x > 180 && y < 120)
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 247, 13)));
					EndPaint(hWnd, &ps);
				}
				if ( x>0 && x < 180 && y < 120 && y >0)
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 0, 0)));
					EndPaint(hWnd, &ps);
				}
				if (x < 180 && y > 120)
				{
					BeginPaint(hWnd, &ps);

					FillRect(ps.hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 255, 26)));
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
				if (LOWORD(wParam) == 51 && HIWORD(lParam) == 4)  // Ctrl+3(ëåâûé êîíòðîë) Íåîáõîäèìî ïåðåäåëàòü íà Ctrl+ Q
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

	wc.lpszClassName = "MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;
	
	hwnd = CreateWindow(wc.lpszClassName, "Ñåëåäêîâ Âèòàëèé ÁÀÑ-2018", WS_OVERLAPPEDWINDOW, 0, 0, 320, 240, nullptr, nullptr, wc.hInstance, nullptr);

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
