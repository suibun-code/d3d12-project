#include <windows.h>

HWND ghMainWnd = 0;

bool InitWindowsApp(HINSTANCE instanceHandle, int show);
int Run();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	if (!InitWindowsApp(hInstance, nShowCmd))
		return 0;

	return Run();
}

bool InitWindowsApp(HINSTANCE hInstance, int show)
{
	HICON hIcon;
	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(106));

	HCURSOR hCursor;
	hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(105));

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = hIcon;
	wc.hCursor = hCursor;
	wc.hbrBackground = CreateSolidBrush(RGB(230, 230, 250));
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWndClass";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	//Create window
	ghMainWnd = CreateWindow(
		L"MainWndClass",
		L"spirit3D - Game Engine Development II - Ramin Amiri",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, //xPos
		CW_USEDEFAULT, //yPos
		CW_USEDEFAULT, //width
		CW_USEDEFAULT, //height
		0,
		0,
		hInstance,
		0);

	if (ghMainWnd == 0)
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		return false;
	}

	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

int Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}
	}



	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//case WM_LBUTTONDOWN:
	//	MessageBox(0, L"Hello World", L"Hello", MB_OK);
	//	return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}