# Liwepaper
Open source live wallpaper program for MS Windows

Liwepaper is an open source live wallpaper application for Windows. I am writing it just for fun and to refresh my knowledge of C and Win32 API programming. It is in a very early stage and may contain bugs and errors. Use at your own risk.

The most important library used in Liwepaper is [weebp](https://github.com/Francesco149/weebp) by [Francesco149](https://github.com/Francesco149). Weebp is an open source wallpaper engine, which can set any window or video as wallpaper on your desktop. It is available as an executable file or as a C library.

## Usage
Download [mpv](https://mpv.io/) (a free, open source, and cross-platform media player) and put it in the same directory as Liwepaper executable. Also put your video for live wallpaper in the same directory and rename it as "video.mp4". Run Liwepaper and click "Start" button.

## Features
- Liwepaper automatically stops video player when fullscreen 3d application is running or when a PowerPoint/LibreOffice presentation is detected.
- Notification icon is displayed in the System Tray. It displays various shortcuts like start, stop, open window and quit application.

## TODO
- Rewrite application using modern C/C++ GUI library.
- Embed video player in the Liwepaper application.
- Implement keyboard shortcuts.
