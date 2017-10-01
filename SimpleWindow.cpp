#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam);
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInst, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { };
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"MYCLASS";
	if (!RegisterClass(&wc))
		return -1;
	HWND hwnd = CreateWindowEx(0,L"MYCLASS", L"LEARN", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);

	MSG msg = {NULL};
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,msg,WParam,LParam);
	}
}