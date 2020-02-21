#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include "liwepaper.h"
#include "liwepaper_gui.h"

//CreateWindowEx
HWND CrWin(LPCSTR CLASS_NAME, LPCSTR winText, HINSTANCE hInstance)
{
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		winText,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 420,
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
	nid.hIcon = loadImage("icon.ico");

	return nid;
}

HMENU CrPopupMenu()
{

	HMENU popupMenu = CreatePopupMenu();
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_OPEN, "Open");
	AppendMenu(popupMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_START, "Start");
	AppendMenu(popupMenu, MF_STRING, APPWM_TRAY_STOP, "Stop");

	return popupMenu;
}

void changeStaticColor(HDC hdcStatic)
{
	SetBkColor(hdcStatic, RGB(32, 32, 32));
	SetTextColor(hdcStatic, RGB(255, 255, 255));
}

void drawControls(HWND hwnd)
{
	HWND line1 = CrLine(hwnd, 70, 50, 480, 20);

	HWND static1 = CrStatic(hwnd, "Path to video player:", 70, 70, 480, 20);
	HWND edit1 = CrEdit(hwnd, playerPath, 70, 90, 480, 20, APPWM_EDIT1);

	HWND static2 = CrStatic(hwnd, "Parameters for video player:", 70, 130, 480, 20);
	HWND edit2 = CrEdit(hwnd, playerParams, 70, 150, 480, 20, APPWM_EDIT2);

	HWND button1 = CrButton(hwnd, "Start", 70, 210, 220, 40, APPWM_BUTTON1);
	HWND button2 = CrButton(hwnd, "Stop", 335, 210, 220, 40, APPWM_BUTTON2);

	HWND check1 = CrCheck(hwnd, "Launch at startup", 70, 270, 220, 20, APPWM_CHECK1, 1);

	HWND line2 = CrLine(hwnd, 70, 310, 480, 20);

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
