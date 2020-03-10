#ifndef _WINAPI_HELP_H_
#define _WINAPI_HELP_H_

UINT_PTR setTimer(HWND, UINT_PTR, UINT);
int getNotificationState();
BOOL CALLBACK EnumWindowsHwndCallback(HWND, LPARAM);
HANDLE shellExec(LPCWSTR, LPCWSTR);
HICON loadImage(LPCWSTR);
int createShortcut(LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR);
int deleteShortcut(LPCWSTR, LPCWSTR);
DWORD getPID(HANDLE);
HWND getHwndFromHandle(HANDLE);
void setWindowStyle(HWND, long);
void hideWindow(HWND);
void showWindow(HWND);

HWND ghwnd;

#endif
