@echo off
pushd ..\
call vendor\premake\premake5\premake5.exe vs2019
popd
PAUSE