#include <windows.h>
#include <gdiplus.h>
#include <math.h>
#include <ctime>
#include <vector>
#include "resource.h"
#pragma comment(lib, "gdiplus.lib")

HWND hCombo1;
CHAR string_1[] = { "1" };
int NumberOfThreads = 1;
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

struct RGB
{
	int R = rand() % 255;
	int G = rand() % 255;
	int B = rand() % 255;
};

struct Thread
{
	RGB rgb;
	int Radius;
};

std::vector <RGB> color(1);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusstartupinput, nullptr);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),0,(DlgProc),0);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

void Draw(HDC hdc,int R,int G,int B)
{
	POINT ptCenter;
	int radius = 30;
	ptCenter.x = rand() % 600;
	ptCenter.y = rand() % 400;
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255,R,G,B));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, R,G,B));
	Sleep(100);
	gf.FillEllipse(&brush, ptCenter.x, ptCenter.y, radius, radius);
}



DWORD WINAPI PaintCurcle(const LPVOID lpParam)
{
	srand(time(NULL));
	CONST HDC hdc = (CONST HDC)lpParam;
	int R = rand() % 255;
	int G = rand() % 255;
	int B = rand() % 255;
	for (int i = 0; true; i++)
	{
		Sleep(100);
		Draw(hdc,R,G,B);
	}
	return 0;
}


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::vector <HANDLE> Threads;
	//DWORD* thrID = new DWORD[NumberOfThreads];
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			hCombo1 = GetDlgItem(hwnd, IDC_COMBO1);
			SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)string_1);
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_COMBO1:
				{
					if (HIWORD(wParam) == CBN_SELENDOK)
					{
						char str_1[255];
						int i = SendMessage(hCombo1, CB_GETCURSEL, 0, 0);
						SendMessage(hCombo1, CB_GETLBTEXT, i, (LPARAM)str_1);
					}
					break;
				}
				case IDNEWTHREAD:
				{
					NumberOfThreads++;
					InvalidateRect(hwnd, NULL, TRUE);
					break;
				}	
				case IDDELETETHREAD:
				{
					InvalidateRect(hwnd, NULL, TRUE);
					break;
				}
			}
			break;
		}
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			for (int i = 0; i < NumberOfThreads; i++)
			{
				Threads.push_back(CreateThread(NULL, 0, &PaintCurcle, hdc, 0, NULL));
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
