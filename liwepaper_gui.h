#ifndef _LIWEPAPER_GUI_H_
#define _LIWEPAPER_GUI_H_

#define APPWM_ICONNOTIFY (WM_APP + 1)

#define APPWM_TRAY_ICON (WM_APP + 10)
#define APPWM_TRAY_OPEN (WM_APP + 11)
#define APPWM_TRAY_START (WM_APP + 12)
#define APPWM_TRAY_STOP (WM_APP + 13)
#define APPWM_TRAY_EXIT (WM_APP + 14)

#define APPWM_TIMER (WM_APP + 20)

#define APPWM_EDIT1 (WM_APP + 30)
#define APPWM_EDIT2 (WM_APP + 31)
#define APPWM_BUTTON1 (WM_APP + 32)
#define APPWM_BUTTON2 (WM_APP + 33)
#define APPWM_CHECK1 (WM_APP + 34)

#define APPWM_LINE (WM_APP + 35)

HWND CrWin(LPCSTR, LPCSTR, HINSTANCE);
HWND CrEdit(HWND, LPCSTR, UINT, UINT, UINT, UINT, UINT_PTR);
HWND CrButton(HWND, LPCSTR, UINT, UINT, UINT, UINT, UINT_PTR);
HWND CrStatic(HWND, LPCSTR, UINT, UINT, UINT, UINT);
HWND CrLine(HWND, UINT, UINT, UINT, UINT);
HWND CrCheck(HWND, LPCSTR, UINT, UINT, UINT, UINT, UINT_PTR, int);
NOTIFYICONDATA CrNotifyIcon(HWND, LPCSTR);
HMENU CrPopupMenu();
void changeStaticColor(HDC);
void drawControls(HWND);
void handlePaint(HWND);
void handleCheckBox(HWND);
void OpenContextMenu(HWND, HMENU);
void handleTrayIconDblCl(HWND);

#endif
