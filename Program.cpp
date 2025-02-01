#include <Windows.h>
#include "Document.h"

#define TID_DROP 1032

void OnCreate(HWND hWnd, CREATESTRUCT* pcs)
{
	Document* doc = Document::GetSingleton();
	doc->MakeDiagram();
	SetTimer(hWnd, TID_DROP, 500, 0);
}

void OnTimer(HWND hWnd, DWORD tid)
{
	Document* doc = Document::GetSingleton();
	if (doc->MoveDown() == false) {

	}
	InvalidateRect(hWnd, 0, true);
}

void MoveLeftProc(HWND hWnd)
{
	Document* doc = Document::GetSingleton();
	doc->MoveLeft();
}

void MoveRightProc(HWND hWnd)
{
	Document* doc = Document::GetSingleton();
	doc->MoveRight();
}

void OnKeyDown(HWND hWnd, DWORD key, LPARAM lParam)
{
	switch (key) {
	case VK_LEFT: MoveLeftProc(hWnd); break;
	case VK_RIGHT: MoveRightProc(hWnd); break;
	}

	InvalidateRect(hWnd, 0, true);
}

void OnDraw(HWND hWnd, HDC hdc)
{
	DrawGameBoard(hWnd, hdc);
	DrawDiagram(hWnd, hdc);
	
	DrawNextBoard(hWnd, hdc);
	DrawNextDiagram(hWnd, hdc);
}

void  OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	OnDraw(hWnd, hdc);
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
}

LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE: OnCreate(hWnd, (CREATESTRUCT*)lParam); return 0;
	case WM_TIMER: OnTimer(hWnd, (DWORD)wParam); return 0;
	case WM_KEYDOWN: OnKeyDown(hWnd, (DWORD)wParam, lParam); return 0;
	case WM_PAINT: OnPaint(hWnd); return 0;
	case WM_DESTROY: OnDestroy(hWnd, wParam, lParam); return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
	WNDCLASS wndclass = { 0 };
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.style = CS_DBLCLKS;
	wndclass.lpfnWndProc = MainProc;
	wndclass.lpszClassName = TEXT("테트리스");
	wndclass.hCursor = LoadCursor(0, IDC_ARROW);
	wndclass.hIcon = LoadCursor(0, IDI_APPLICATION);
	wndclass.hInstance = hIns;

	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		TEXT("테트리스"), TEXT("테트리스"), 
		WS_OVERLAPPED, 100, 100, 410, 400, 
		0, 0, hIns, 0);
	ShowWindow(hWnd, nShow);

	MSG Message;
	while(GetMessage(&Message, 0, 0, 0)) {
		DispatchMessage(&Message);
	}

	return 0;
}