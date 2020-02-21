#define WP_IMPLEMENTATION
#include "weebp/weebp.c"
#include "liwepaper.h"
#include "winapi_help.h"

DWORD PID = NULL;
LPCSTR playerPath = "mpv.exe";
LPCSTR playerParams = "--vo=gpu --gpu-context=d3d11 --hwdec=d3d11va --terminal=no --loop=inf --audio=no --fs \"video.mp4\"";

int VP_RUNNING = 0;
int VP_INTERRUPTED = 0;

void start()
{
	if (VP_RUNNING)
		return;

	if (VP_INTERRUPTED)
		return;

	PID = run(playerPath, playerParams, 333);
	EnumWindows(EnumWindowsProcMy, PID);

	HWND w = NULL;
	if (ghwnd != NULL)
		w = ghwnd;

	wp_add(w);
	wp_fullscreen(w);

	VP_RUNNING = 1;
}

void stop()
{
	if (VP_RUNNING)
	{
		HANDLE procHandle = OpenProcess(PROCESS_TERMINATE, 0, PID);
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


DWORD run(LPCSTR file, LPCSTR parameters, int wait)
{
	DWORD PID = shellExec(file, parameters);
	Sleep(wait);

	return PID;
}
