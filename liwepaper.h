#ifndef _LIWEPAPER_H_
#define _LIWEPAPER_H_

void start();
void stop();
void checkState();
HANDLE run(LPCSTR, LPCSTR, int);
void setStartup();

HANDLE pHandle;
LPCSTR playerPath;
LPCSTR playerParams;

int VP_RUNNING;
int VP_INTERRUPTED;

#endif