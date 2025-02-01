#include <Windows.h>

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
	HWND hWnd = CreateWindow(TEXT("테트리스"), TEXT("테트리스"), WS_OVERLAPPED, 100, 100, 410, 400);

	return 0;
}