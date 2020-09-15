#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <stdio.h>

#include "winapi_help.h"
#include "liwepaper.h"
#include "liwepaper_gui.h"
#include "resources.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HMENU hMenu = NULL;
NOTIFYICONDATA nid = { 0 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	int onStartup = 0;
	if (strlen(lpCmdLine) > 0)
		onStartup = 1;

	// Register the window class.
	LPCWSTR CLASS_NAME = L"LIWEPAPER_WINDOW_CLASS";
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
	HWND hwnd = CrWin(CLASS_NAME, L"Liwepaper 1.0", hInstance);
	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, SW_SHOWNORMAL - onStartup);

	// Create the notification icon
	nid = CrNotifyIcon(hwnd, L"liwepaper_notifyicon");

	// Show the notification icon
	Shell_NotifyIcon(NIM_ADD, &nid);

	// Create the font
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Corbel");
	//HFONT hFontDef = GetStockObject(DEFAULT_GUI_FONT);

	// Create and start timer
	UINT_PTR timer = setTimer(hwnd, APPWM_TIMER, 1500);

	// Draw window controls
	drawControls(hwnd, hFont, onStartup);
	//drawControls(hwnd, hFontDef, onStartup);
	//drawControls(hwnd, NULL, onStartup);

	// Create the popup menu
	hMenu = CrPopupMenu();

	if (onStartup)
		start();

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
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		handlePaint(hwnd);
		return 0;

	case APPWM_ICONNOTIFY:

		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
			showWindow(hwnd);
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
			if (handleCheckBox(hwnd))
				setStartup();
			else
				unsetStartup();
			break;
		case APPWM_TRAY_OPEN:
			showWindow(hwnd);
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
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_SYSCOMMAND:
		switch (LOWORD(wParam)) {
		case SC_MINIMIZE:
			hideWindow(hwnd);
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
