#include "framework.h"
#include "WindowTetris.h"
#include "Document.h"

#define BOARD_SX	70
#define BOARD_SY	50
#define MY_WIDTH	15
#define MY_HEIGHT	15

#define MY_RX(x)	(BOARD_SX + (x)*MY_WIDTH)
#define MY_RY(y)	(BOARD_SY + (y)*MY_HEIGHT)
#define NEXT_SX		270
#define MY_NRX(x)	(NEXT_SX + (x)*MY_WIDHT)
#define MY_NRY(y)	(MY_RY(y))

#define DIAGRAM_WIDTH	4
#define DIAGRAM_HEIGHT	4
#define DW			DIAGRAM_WIDTH
#define DH			DIAGRAM_HEIGHT

#define TID_DROP	1032

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

void DrawGameBoard(HWND hWnd, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(40, 40, 40));
	HPEN oPen = (HPEN)SelectObject(hdc, hPen);

	for (int r = 0; r <= BOARD_ROW; r++) {
		MoveToEx(hdc, BOARD_SX, MY_RY(r), 0);
		LineTo(hdc, MY_RX(BOARD_COL), MY_RY(r));
	}

	for (int c = 0; c <= BOARD_COL; c++) {
		MoveToEx(hdc, MY_RX(c), MY_RY(0), 0);
		LineTo(hdc, MY_RX(c), MY_RY(BOARD_ROW));
	}

	SelectObject(hdc, hPen);
	DeleteObject(hPen);
}

void DrawDiagram(HWND hWnd, HDC hdc)
{

}

void DrawNextBoard(HWND hWnd, HDC hdc)
{

}

void DrawNextDiagram(HWND hWnd, HDC hdc)
{

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
	PostQuitMessage(0);
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

int APIENTRY wWinMain(_In_ HINSTANCE hIns,
	_In_opt_ HINSTANCE hPrev,
	_In_ LPWSTR    cmd,
	_In_ int       nShow)
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
	while (GetMessage(&Message, 0, 0, 0)) {
		DispatchMessage(&Message);
	}

	return 0;
}

