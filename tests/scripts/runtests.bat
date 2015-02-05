@echo off
set DIR=%~dp0
set PATH=%PATH%;%DIR%\..\src
rm -rf data/libtorrent data/uTorrent 2>&1 > NUL
unzip data/libtorrent.zip -d data > NUL
unzip data/uTorrent.zip -d data > NUL
%DIR%\tests.exe
