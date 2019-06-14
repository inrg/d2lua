@echo off
REM	Use Vc++ 6.0 to build
cl -I.. /c /Ox *.c
link *.obj kernel32.lib user32.lib msvcrt.lib /def:template.def /dll /nodefaultlib /opt:nowin98 /merge:.text=.data /ignore:4078
copy /y *.dll ..
pause
