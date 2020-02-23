#include <windows.h>
#include <stdio.h>

#include "winapi_help.h"
#include "liwepaper.h"
#include "liwepaper_gui.h"
#include "resources.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HMENU hMenu = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	LPCSTR CLASS_NAME = "LIWEPAPER_WINDOW_CLASS";
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = CreateSolidBrush(0x00202020);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	RegisterClassEx(&wc);

	// Create the window.
	HWND hwnd = CrWin(CLASS_NAME, "Liwepaper v0.1", hInstance);
	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, nCmdShow);
	// Create the notification icon
	NOTIFYICONDATA nid = CrNotifyIcon(hwnd, "liwepaper_notifyicon");

	// Show the notification icon
	Shell_NotifyIcon(NIM_ADD, &nid);

	// Create the popup menu
	hMenu = CrPopupMenu();

	// Create and start timer
	UINT_PTR timer = setTimer(hwnd, APPWM_TIMER, 2000);

	// Draw window controls
	drawControls(hwnd);

	// Run the message loop.
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		stop();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		handlePaint(hwnd);
		return 0;

	case APPWM_ICONNOTIFY:

		switch (lParam)
		{
			case WM_LBUTTONDBLCLK:
				handleTrayIconDblCl(hwnd);
			break;

			case WM_RBUTTONDOWN:
				case WM_CONTEXTMENU:
					OpenContextMenu(hwnd, hMenu);
					break;
		}
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case APPWM_BUTTON1:
			start();
			break;

		case APPWM_BUTTON2:
			stop();
			break;

		case APPWM_CHECK1:
			handleCheckBox(hwnd);
			break;
		case APPWM_TRAY_OPEN:
			handleTrayIconDblCl(hwnd);
			break;

		case APPWM_TRAY_START:
			start();
			break;

		case APPWM_TRAY_STOP:
			stop();
			break;

		case APPWM_TRAY_EXIT:
			stop();
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_SYSCOMMAND:
		switch (LOWORD(wParam)) {
			case SC_MINIMIZE:

				ShowWindow(hwnd, SW_HIDE);
				break;
		}
		break;

	case WM_CTLCOLORSTATIC:
	{
		changeStaticColor((HDC)wParam);
		return (LRESULT)GetStockObject(NULL_BRUSH);
	}
	break;

	case WM_TIMER:
		switch (wParam) 
		{
			case APPWM_TIMER:
				checkState();
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
