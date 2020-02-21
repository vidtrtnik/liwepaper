#ifndef _LIWEPAPER_H_
#define _LIWEPAPER_H_

void start();
void stop();
void checkState();
DWORD run(LPCSTR, LPCSTR, int);

DWORD PID;
LPCSTR playerPath;
LPCSTR playerParams;

int VP_RUNNING;
int VP_INTERRUPTED;

#endif