#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <strsafe.h>
#include "liwepaper.h"
#include "liwepaper_gui.h"
#include "resources.h"

//CreateWindowEx
HWND CrWin(LPCSTR CLASS_NAME, LPCSTR winText, HINSTANCE hInstance)
{
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		winText,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 440,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	return hwnd;
}

HWND CrEdit(HWND hwnd, LPCSTR text, UINT px, UINT py, UINT sx, UINT sy, UINT_PTR ID)
{
	HWND edit = CreateWindow(
		"Edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		px, py, sx, sy,
		hwnd, (HMENU)NULL, NULL, NULL);

	SetWindowText(edit, text);

	return edit;
}

HWND CrButton(HWND hwnd, LPCSTR text, UINT px, UINT py, UINT sx, UINT sy, UINT_PTR ID)
{
	HWND button = CreateWindow(
		"Button", text,
		WS_VISIBLE | WS_CHILD | BS_FLAT,
		px, py, sx, sy,
		hwnd, (HMENU)ID, NULL, NULL);

	return button;
}

HWND CrStatic(HWND hwnd, LPCSTR text, UINT px, UINT py, UINT sx, UINT sy)
{
	HWND tstatic = CreateWindow(
		"Static", text,
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		px, py, sx, sy,
		hwnd, (HMENU)NULL, NULL, NULL);

	return tstatic;
}

HWND CrBitmap(HWND hwnd, LPCSTR path, UINT px, UINT py, UINT sx, UINT sy)
{
	HWND bitmap = CreateWindow(
		"Static", NULL,
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		px, py, sx, sy,
		hwnd, (HMENU)NULL, NULL, NULL);

	HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_LOGO));
	SendMessage(bitmap, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

	return bitmap;
}

HWND CrLine(HWND hwnd, UINT px, UINT py, UINT sx, UINT sy)
{
	HWND tstatic = CreateWindow(
		"Static", "",
		WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ,
		px, py, sx, sy,
		hwnd, (HMENU)NULL, NULL, NULL);

	return tstatic;
}

HWND CrCheck(HWND hwnd, LPCSTR text, UINT px, UINT py, UINT sx, UINT sy, UINT_PTR ID, int checked)
{
	HWND checkb = CreateWindow(
		"Button", text,
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		px, py, sx, sy,
		hwnd, (HMENU)ID, NULL, NULL);

	if (checked == 1)
		CheckDlgButton(hwnd, ID, BST_CHECKED);
	else
		CheckDlgButton(hwnd, ID, BST_UNCHECKED);

	//CheckDlgButton(hwnd, ID, BST_INDETERMINATE);
	return checkb;
}

NOTIFYICONDATA CrNotifyIcon(HWND hwnd, LPCSTR text)
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uID = APPWM_TRAY_ICON;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.uCallbackMessage = APPWM_ICONNOTIFY;
	nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));

	return nid;
}

HMENU CrPopupMenu()
{

	HMENU popupMenu = CreatePopupMenu();
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_OPEN, "Open");
	AppendMenu(popupMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_START, "Start");
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_STOP, "Stop");
	AppendMenu(popupMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_EXIT, "Exit");

	return popupMenu;
}

void changeStaticColor(HDC hdcStatic)
{
	SetBkColor(hdcStatic, RGB(32, 32, 32));
	SetTextColor(hdcStatic, RGB(255, 255, 255));
}

void drawControls(HWND hwnd)
{
	HWND logo = CrBitmap(hwnd, NULL, 100, 15, 420, 130);

	HWND line1 = CrLine(hwnd, 60, 150, 500, 20);

	HWND static1 = CrStatic(hwnd, "Path to video player:", 60, 170, 500, 20);
	HWND edit1 = CrEdit(hwnd, playerPath, 60, 190, 500, 20, APPWM_EDIT1);

	HWND static2 = CrStatic(hwnd, "Parameters for video player:", 60, 230, 500, 20);
	HWND edit2 = CrEdit(hwnd, playerParams, 60, 250, 500, 20, APPWM_EDIT2);

	HWND button1 = CrButton(hwnd, "Start", 60, 310, 200, 40, APPWM_BUTTON1);
	HWND button2 = CrButton(hwnd, "Stop", 360, 310, 200, 40, APPWM_BUTTON2);

	HWND check1 = CrCheck(hwnd, "Launch at startup", 60, 370, 220, 20, APPWM_CHECK1, 1);

	HWND line2 = CrLine(hwnd, 60, 410, 500, 20);

	EnableWindow(edit1, 0);
	EnableWindow(edit2, 0);
}

void handlePaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	EndPaint(hwnd, &ps);
}

void handleCheckBox(HWND hwnd)
{
	BOOL checked = IsDlgButtonChecked(hwnd, APPWM_CHECK1);

	if (checked)
		CheckDlgButton(hwnd, APPWM_CHECK1, BST_UNCHECKED);

	else
		CheckDlgButton(hwnd, APPWM_CHECK1, BST_CHECKED);
}

void OpenContextMenu(HWND hWnd, HMENU cMenu)
{
	POINT curPoint;
	GetCursorPos(&curPoint);

	SetForegroundWindow(hWnd);

	UINT clicked = TrackPopupMenu(
		cMenu, 0,
		curPoint.x, curPoint.y,
		0, hWnd, NULL);
}

void handleTrayIconDblCl(HWND hwnd)
{
	ShowWindow(hwnd, SW_RESTORE);
	SetForegroundWindow(hwnd);
}
