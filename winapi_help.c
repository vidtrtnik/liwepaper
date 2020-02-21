#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include "winapi_help.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

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
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
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

DWORD shellExec(LPCSTR lpFile, LPCSTR lpParameters)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = lpFile;
	ShExecInfo.lpParameters = lpParameters;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_MAXIMIZE;
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);
	return GetProcessId(ShExecInfo.hProcess);
}

HICON loadImage(LPCSTR path)
{
	HICON icon = LoadImage(NULL, path, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	return icon;
}