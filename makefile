# Liwepaper makefile

all: liwepaper.exe

.c.obj:
  cl /O1 /c $*.c

.rc.res:
  rc /r $*.rc

liwepaper.exe: main.obj liwepaper.obj liwepaper_gui.obj winapi_help.obj resources.res
  link /OUT:liwepaper.exe main.obj liwepaper.obj liwepaper_gui.obj winapi_help.obj resources.res

clean:
  del main.obj liwepaper.obj liwepaper_gui.obj winapi_help.obj
  del resources.res