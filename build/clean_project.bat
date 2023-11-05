@echo off
rem Build files
cd ../
rmdir /s /q bin
rmdir /s /q bin-int

rem Configuration files\
del *.sln
for /R %%i in (.vcxproj) do if exist "%%i" del /Q "%%i"
for /R %%i in (.vcxproj.filters) do if exist "%%i" del /Q "%%i"
for /R %%i in (.vcxproj.user) do if exist "%%i" del /Q "%%i"


PAUSE