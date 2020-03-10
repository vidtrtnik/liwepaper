#ifndef _LIWEPAPER_H_
#define _LIWEPAPER_H_

void start();
void stop();
void checkState();
HANDLE run(LPCWSTR, LPCWSTR, int);
void setStartup();

HANDLE pHandle;
LPCWSTR playerPath;
LPCWSTR playerParams;

int VP_RUNNING;
int VP_INTERRUPTED;

#endif
