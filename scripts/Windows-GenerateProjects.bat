@echo off
pushd ..\
call vendor\compiled\premake\premake5.exe vs2019
popd
PAUSE