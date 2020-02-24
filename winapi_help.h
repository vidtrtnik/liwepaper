#ifndef _WINAPI_HELP_H_
#define _WINAPI_HELP_H_

UINT_PTR setTimer(HWND, UINT_PTR, UINT);
int getNotificationState();
BOOL CALLBACK EnumWindowsHwndCallback(HWND, LPARAM);
HANDLE shellExec(LPCSTR, LPCSTR);
HICON loadImage(LPCSTR);
int createShortcut(LPCSTR, LPCSTR, LPCSTR, LPCSTR);
int deleteShortcut(LPCSTR, LPCSTR);
DWORD getPID(HANDLE);
HWND getHwndFromHandle(HANDLE);
void setWindowStyle(HWND, long);
void hideWindow(HWND);
void showWindow(HWND);

HWND ghwnd;

#endif