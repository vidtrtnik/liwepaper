#define WP_IMPLEMENTATION

#include "weebp/weebp.c"
#include "liwepaper.h"
#include "winapi_help.h"

HANDLE procHandle = NULL;
LPCSTR playerPath = "mpv.exe";
LPCSTR playerParams = "--vo=gpu --gpu-context=d3d11 --hwdec=d3d11va --terminal=no --no-input-default-bindings --loop=inf --audio=no --fs \"video.mp4\"";

int VP_RUNNING = 0;
int VP_INTERRUPTED = 0;

void start()
{
	if (VP_RUNNING)
		return;

	if (VP_INTERRUPTED)
		return;

	procHandle = run(playerPath, playerParams, 333);

	HWND w = getHwndFromHandle(procHandle);

	wp_add(w);
	wp_fullscreen(w);

	VP_RUNNING = 1;
}

void stop()
{
	if (VP_RUNNING)
	{
		TerminateProcess(procHandle, 1);
		CloseHandle(procHandle);

		VP_RUNNING = 0;
		VP_INTERRUPTED = 0;
	}
}

void checkState()
{
	int state = getNotificationState();
	if ((state == 2 || state == 3 || state == 4) && state != -1)
	{
		if (VP_RUNNING)
		{
			stop();
			VP_INTERRUPTED = 1;
		}
	}
	else
	{
		if (VP_INTERRUPTED)
		{
			VP_INTERRUPTED = 0;
			start();
		}
	}
}


HANDLE run(LPCSTR file, LPCSTR parameters, int wait)
{
	HANDLE pHandle = shellExec(file, parameters);
	Sleep(wait);

	return pHandle;
}

void setStartup()
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	TCHAR szDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szDir);

	createShortcut(szPath, "1", szDir, szPath, "Liwepaper");
}

void unsetStartup()
{
	TCHAR szDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szDir);

	deleteShortcut("Liwepaper.lnk", szDir);
}