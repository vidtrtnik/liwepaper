#ifndef _WINAPI_HELP_H_
#define _WINAPI_HELP_H_

UINT_PTR setTimer(HWND, UINT_PTR, UINT);
int getNotificationState();
BOOL CALLBACK EnumWindowsProcMy(HWND, LPARAM);
DWORD shellExec(LPCSTR, LPCSTR);
HICON loadImage(LPCSTR);

HWND ghwnd;

#endif