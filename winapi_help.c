#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <Objbase.h>
#include <processthreadsapi.h>
#include "winapi_help.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "kernel32.lib")

UINT_PTR setTimer(HWND hwnd, UINT_PTR ID, UINT interval)
{
	UINT_PTR timer = SetTimer(
		hwnd,
		ID,
		interval,
		(TIMERPROC)NULL);

	return timer;
}

// SHQueryUserNotificationState
int getNotificationState()
{
	/*
	QUNS_NOT_PRESENT              = 1,
	QUNS_BUSY                     = 2,
	QUNS_RUNNING_D3D_FULL_SCREEN  = 3,
	QUNS_PRESENTATION_MODE        = 4,
	QUNS_ACCEPTS_NOTIFICATIONS    = 5,
	QUNS_QUIET_TIME               = 6,
	QUNS_APP                      = 7
	*/

	QUERY_USER_NOTIFICATION_STATE notificationState;
	HRESULT hr = SHQueryUserNotificationState(&notificationState);
	int state = -1;

	if (SUCCEEDED(hr))
	{
		switch (notificationState) {
		case QUNS_NOT_PRESENT:
			state = 1;
			break;
		case QUNS_BUSY:
			state = 2;
			break;
		case QUNS_RUNNING_D3D_FULL_SCREEN:
			state = 3;
			break;
		case QUNS_PRESENTATION_MODE:
			state = 4;
			break;
		case QUNS_ACCEPTS_NOTIFICATIONS:
			state = 5;
			break;
		case QUNS_QUIET_TIME:
			state = 6;
			break;
		case QUNS_APP:
			state = 7;
			break;
		}
	}
	return state;
}

HWND ghwnd = NULL;
BOOL CALLBACK EnumWindowsHwndCallback(HWND hwnd, LPARAM lParam)
{
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == lParam)
	{
		ghwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

HANDLE shellExec(LPCWSTR lpFile, LPCWSTR lpParameters)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = lpFile;
	ShExecInfo.lpParameters = lpParameters;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_MINIMIZE;
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);
	return ShExecInfo.hProcess;
}

HICON loadImage(LPCWSTR path)
{
	HICON icon = LoadImage(NULL, path, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	return icon;
}

int createShortcut(LPCWSTR path, LPCWSTR arguments, LPCWSTR workingDir, LPCWSTR iconLocation, LPCWSTR description)
{
	CoInitialize(NULL);
	IShellLink* pShellLink = NULL;

	HRESULT hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_ALL, &IID_IShellLink, (PVOID*)&pShellLink);
	if (SUCCEEDED(hres))
	{
		pShellLink->lpVtbl->SetPath(pShellLink, path);
		pShellLink->lpVtbl->SetArguments(pShellLink, arguments);
		pShellLink->lpVtbl->SetWorkingDirectory(pShellLink, workingDir);
		pShellLink->lpVtbl->SetDescription(pShellLink, description);
		pShellLink->lpVtbl->SetIconLocation(pShellLink, iconLocation, 0);

		IPersistFile* pPersistFile = NULL;

		hres = pShellLink->lpVtbl->QueryInterface(pShellLink, &IID_IPersistFile, (PVOID*)&pPersistFile);
		if (SUCCEEDED(hres))
		{
			TCHAR stPath[MAX_PATH];
			hres = SHGetSpecialFolderPath(NULL, stPath, CSIDL_STARTUP, 0);
			if (SUCCEEDED(hres))
			{
				if (SetCurrentDirectory(stPath))
				{
					pPersistFile->lpVtbl->Save(pPersistFile, L"Liwepaper.lnk", TRUE);
					pPersistFile->lpVtbl->Release(pPersistFile);
					SetCurrentDirectory(workingDir);
				}
			}
		}

		pShellLink->lpVtbl->Release(pShellLink);

		return 1;
	}

	return 0;
}

int deleteShortcut(LPCWSTR linkName, LPCWSTR workingDir)
{

	TCHAR stPath[MAX_PATH];
	HRESULT hres = SHGetSpecialFolderPath(NULL, stPath, CSIDL_STARTUP, 0);
	if (SUCCEEDED(hres))
	{
		if (SetCurrentDirectory(stPath))
		{
			DeleteFile(linkName);
			SetCurrentDirectory(workingDir);
			return 1;
		}
	}
	return 0;
}

DWORD getPID(HANDLE pHandle)
{
	return GetProcessId(pHandle);
}

HWND getHwndFromHandle(HANDLE pHandle)
{
	DWORD PID = getPID(pHandle);

	ghwnd = NULL;
	EnumWindows(EnumWindowsHwndCallback, PID);

	return ghwnd;
}

void setWindowStyle(HWND hwnd, long flags)
{
	long windowStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	windowStyle &= (flags);

	ShowWindow(hwnd, SW_HIDE);
	SetWindowLong(hwnd, GWL_EXSTYLE, windowStyle);
	ShowWindow(hwnd, SW_SHOW);
}

void hideWindow(HWND hwnd)
{
	ShowWindow(hwnd, SW_MINIMIZE);
	ShowWindow(hwnd, SW_HIDE);
	long windowStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	windowStyle |= WS_EX_TOOLWINDOW;
	windowStyle &= ~(WS_EX_APPWINDOW);

	SetWindowLong(hwnd, GWL_EXSTYLE, windowStyle);
	ShowWindow(hwnd, SW_SHOW);
	ShowWindow(hwnd, SW_MINIMIZE);
	ShowWindow(hwnd, SW_HIDE);
}

void showWindow(HWND hwnd)
{
	setWindowStyle(hwnd, (WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX)));
	ShowWindow(hwnd, SW_SHOW);
}
