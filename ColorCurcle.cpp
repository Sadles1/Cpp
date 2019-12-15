#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include "resource.h"
#pragma comment(lib, "gdiplus.lib")

HWND hCombo1, hCombo2, hCombo3, hEdit, hEditR, hEditB, hEditG;
bool OffThread;

CHAR IDLE[] = { "IDLE" };
CHAR LOWEST[] = { "LOWEST" };
CHAR BELOW_NORMAL[] = { "BELOW NORMAL" };
CHAR NORMAL[] = { "NORMAL" };
CHAR ABOVE_NORMAL[] = { "ABOVE NORMAL" };
CHAR HIGHEST[] = { "HIGHEST" };
CHAR TIME_CRITICAL[] = { "TIME CRITICAL" };

int NumberOfThreads = 1;
int CurrentSelectThread=1;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


struct Thread
{
public:
	struct RGB
	{
		int R = rand() % 255;
		int G = rand() % 255;
		int B = rand() % 255;
	};
	RGB rgb;
	int Radius=rand()%50+10;
	int Priority = 0;
	HDC hdc;
};

std::vector <Thread> ThreadsInfo;
std::vector <HANDLE> Threads;
std::vector <int> LastDelete;
HANDLE MainThread;
static std::pair<bool, HWND> AddWindow(const std::string&& winClass, const std::string&& title, HWND hParentWnd, const WNDPROC callback)
{
	UnregisterClass(winClass.c_str(), GetModuleHandle(nullptr));
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	HWND hWindow{};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.lpfnWndProc = callback;
	wc.lpszClassName = winClass.c_str();
	wc.style = CS_VREDRAW | CS_HREDRAW;
	const auto create_window = [&hWindow, &winClass, &title, &hParentWnd]()->std::pair<bool, HWND>
	{
		if (hWindow = CreateWindow(winClass.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, 300, 300, hParentWnd, nullptr, nullptr, nullptr); !hWindow)
			return{ false,nullptr };

		ShowWindow(hWindow, SW_SHOWDEFAULT);
		UpdateWindow(hWindow);
		return{ true, hWindow };
	};
	if (!RegisterClassEx(&wc))
		return create_window();
	return create_window();
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusstartupinput, nullptr);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),0,(DlgProc),0);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

void Draw(HDC hdc,int R,int G,int B,int radius)
{
	POINT ptCenter;
	ptCenter.x = rand() % (600-radius/2);
	ptCenter.y = rand() % (320-radius/2);
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255,R,G,B));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, R,G,B));
	Sleep(100);
	gf.FillEllipse(&brush, ptCenter.x, ptCenter.y, radius, radius);
}

DWORD WINAPI PaintCurcle(CONST LPARAM Info)
{
	CONST Thread* CurrentThreadInfo = (Thread*)Info;
	CONST HDC hdc = CurrentThreadInfo->hdc;
	int radius = CurrentThreadInfo->Radius;
	int R = CurrentThreadInfo->rgb.R;
	int G = CurrentThreadInfo->rgb.G;
	int B = CurrentThreadInfo->rgb.B;
	while(!OffThread)
	{
		Sleep(100);
		Draw(hdc,R,G,B,radius);
	}
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	srand(time(NULL));
	static HWND hChildWnd{}, hChildEdit{};
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hCombo1 = GetDlgItem(hwnd, IDCOMBO1);
			hCombo2 = GetDlgItem(hwnd, IDCOMBO2);
			hCombo3 = GetDlgItem(hwnd, IDCOMBO3);

			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)IDLE);
			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)LOWEST);
			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)BELOW_NORMAL);
			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)NORMAL);
			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)ABOVE_NORMAL);
			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)HIGHEST);
			SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)TIME_CRITICAL);

			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)IDLE);
			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)LOWEST);
			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)BELOW_NORMAL);
			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)NORMAL);
			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)ABOVE_NORMAL);
			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)HIGHEST);
			SendMessage(hCombo3, CB_ADDSTRING, 0, (LPARAM)TIME_CRITICAL);

			SetThreadPriority(MainThread, 0);

			hEditR= GetDlgItem(hwnd, IDEDITR);
			hEditG= GetDlgItem(hwnd, IDEDITG);
			hEditB = GetDlgItem(hwnd, IDEDITB);
			hEdit = GetDlgItem(hwnd, IDEDITRADIUS);

			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDCOMBO1:
				{
					if (HIWORD(wParam) == CBN_SELENDOK)
					{

						TCHAR text[255];
						int i = SendMessage(hCombo1, CB_GETCURSEL, 0, 0);
						CurrentSelectThread = i;

						snprintf(text, sizeof text, "%i", ThreadsInfo.at(CurrentSelectThread).Radius);
						SetWindowText(hEdit, text);

						snprintf(text, sizeof text, "%i", ThreadsInfo.at(CurrentSelectThread).rgb.R);
						SetWindowText(hEditR, text);

						snprintf(text, sizeof text, "%i", ThreadsInfo.at(CurrentSelectThread).rgb.G);
						SetWindowText(hEditG, text);

						snprintf(text, sizeof text, "%i", ThreadsInfo.at(CurrentSelectThread).rgb.B);
						SetWindowText(hEditB, text);

						switch (GetThreadPriority(Threads.at(CurrentSelectThread)))
						{
							case -15:
							{
								SetWindowText(hCombo2, "IDLE");
								break;
							}
							case -2:
							{
								SetWindowText(hCombo2, "LOWEST");
								break;
							}
							case -1:
							{
								SetWindowText(hCombo2, "BELOW NORMAL");
								break;
							}
							case 0:
							{
								SetWindowText(hCombo2, "NORMAL");
								break;
							}
							case 1:
							{
								SetWindowText(hCombo2, "ABOVE NORMAL");
								break;
							}
							case 2:
							{
								SetWindowText(hCombo2, "HIGHEST");
								break;
							}
							case 15:
							{
								SetWindowText(hCombo2, "TIME CRITICAL");
								break;
							}
						}
					}
					break;
				}
				case IDCOMBO2:
				{
					if (HIWORD(wParam) == CBN_SELENDOK)
					{

						OffThread = 1;
						CHAR text[255];
						int i = SendMessage(hCombo2, CB_GETCURSEL, 0, 0);
						switch (i)
						{
							case 0:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = 1;
								break;
							}
							case 1:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = -1;
								break;

							}
							case 2:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = 2;
								break;

							}
							case 3:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = -15;
								break;

							}
							case 4:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = -2;
								break;

							}
							case 5:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = 0;
								break;

							}
							case 6:
							{
								ThreadsInfo.at(CurrentSelectThread).Priority = 15;
								break;

							}
						}
						Sleep(1000);
						InvalidateRect(hwnd, NULL, TRUE);
						OffThread = 0;

					}
					break;
				}
				case IDCOMBO3:
				{
					if (HIWORD(wParam) == CBN_SELENDOK)
					{

						OffThread = 1;
						CHAR text[255];
						int i = SendMessage(hCombo3, CB_GETCURSEL, 0, 0);
						switch (i)
						{
						case 0:
						{
							SetThreadPriority(MainThread, 1);
							break;
						}
						case 1:
						{
							SetThreadPriority(MainThread, -1);
							break;

						}
						case 2:
						{
							SetThreadPriority(MainThread, 2);
							break;

						}
						case 3:
						{
							SetThreadPriority(MainThread, -15);
							break;

						}
						case 4:
						{
							SetThreadPriority(MainThread, -2);
							break;

						}
						case 5:
						{
							SetThreadPriority(MainThread, 0);
							break;

						}
						case 6:
						{
							SetThreadPriority(MainThread, 15);
							break;

						}
						}
						Sleep(10);

						InvalidateRect(hwnd, NULL, TRUE);
						OffThread = 0;

					}
					break;
				}
				case 1:
				{
					OffThread = 1;

					CHAR r[16],g[16],b[16],radius[16];

					SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)radius);

					SendMessage(hEditR, WM_GETTEXT, MAX_PATH, (LPARAM)r);
					SendMessage(hEditG, WM_GETTEXT, MAX_PATH, (LPARAM)g);
					SendMessage(hEditB, WM_GETTEXT, MAX_PATH, (LPARAM)b);

					ThreadsInfo.at(CurrentSelectThread).Radius = atoi(radius);

					ThreadsInfo.at(CurrentSelectThread).rgb.R = atoi(r);
					ThreadsInfo.at(CurrentSelectThread).rgb.G = atoi(g);
					ThreadsInfo.at(CurrentSelectThread).rgb.B = atoi(b);

					Sleep(200);

					InvalidateRect(hwnd, NULL, TRUE);
					OffThread = 0;

					break;
				}
				case IDNEWTHREAD:
				{
					NumberOfThreads++;
					
					TCHAR text[1000];

					
					if (LastDelete.size() > 0)
					{
						snprintf(text, sizeof text, "%i", LastDelete.at(LastDelete.size()-1));
						LastDelete.pop_back();
					}
					else
					{
						snprintf(text, sizeof text, "%i", NumberOfThreads - 1);
					}
					SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)((LPSTR)text));

					OffThread = 1;

					Thread NewThreadsInfo;

					ThreadsInfo.push_back(NewThreadsInfo);

					ThreadsInfo.at(NumberOfThreads-2).Radius = rand() % 50+10;
					ThreadsInfo.at(NumberOfThreads-2).rgb.R = rand() % 255;
					ThreadsInfo.at(NumberOfThreads-2).rgb.G = rand() % 255;
					ThreadsInfo.at(NumberOfThreads-2).rgb.B = rand() % 255;


					InvalidateRect(hwnd, NULL, TRUE);

					
					Sleep(500);
					OffThread = 0;
					break;
				}	
				case IDDELETETHREAD:
				{
					if (NumberOfThreads > 1)
					{
						TCHAR text[1000];

						OffThread = 1;


						SetWindowText(hCombo1, "");
						SetWindowText(hCombo2, "");
						SetWindowText(hEdit, "");
						SetWindowText(hEditR, "");
						SetWindowText(hEditG, "");
						SetWindowText(hEditB, "");

						LastDelete.push_back(CurrentSelectThread+1);
						SendMessage(hCombo1, CB_DELETESTRING, CurrentSelectThread, NULL);
						Threads.erase(Threads.begin() + CurrentSelectThread);
						ThreadsInfo.erase(ThreadsInfo.begin() + CurrentSelectThread);

						NumberOfThreads--;

						InvalidateRect(hwnd, NULL, TRUE);

						Sleep(500);
						OffThread = 0;
					}
					break;

				}
			}
			break;
		}
		case WM_PAINT:
		{
			srand(time(NULL));
			hdc = BeginPaint(hwnd, &ps);
			for (int i = 0; i < ThreadsInfo.size(); i++)
			{
				Sleep(100);
				Thread CurrentThreadInfo;
				CurrentThreadInfo.hdc = hdc;
				CurrentThreadInfo.Radius = ThreadsInfo.at(i).Radius;
				CurrentThreadInfo.rgb.R = ThreadsInfo.at(i).rgb.R;
				CurrentThreadInfo.rgb.G = ThreadsInfo.at(i).rgb.G;
				CurrentThreadInfo.rgb.B = ThreadsInfo.at(i).rgb.B;
				CurrentThreadInfo.Priority = ThreadsInfo.at(i).Priority;

				if (i < Threads.size())
					Threads.at(i) = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PaintCurcle, (LPVOID)&CurrentThreadInfo, 0, NULL);
				else
					Threads.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PaintCurcle, (LPVOID)&CurrentThreadInfo, 0, NULL));

				SetThreadPriority(Threads.at(i), CurrentThreadInfo.Priority);
			}
			
			switch (GetThreadPriority(MainThread))
			{
				case -15:
				{
					SetWindowText(hCombo3, "IDLE");
					break;
				}
				case -2:
				{
					SetWindowText(hCombo3, "LOWEST");
					break;
				}
				case -1:
				{
					SetWindowText(hCombo3, "BELOW NORMAL");
					break;
				}
				case 0:
				{
					SetWindowText(hCombo3, "NORMAL");
					break;
				}
				case 1:
				{
					SetWindowText(hCombo3, "ABOVE NORMAL");
					break;
				}
				case 2:
				{
					SetWindowText(hCombo3, "HIGHEST");
					break;
				}
				case 15:
				{
					SetWindowText(hCombo3, "TIME CRITICAL");
					break;
				}

			}
			return 0;
		}
		case WM_CLOSE:
		{
			EndDialog(hwnd, 0);
			return 0;
		}
	}
	return 0;
}
