@echo off
net session >nul 2>nul
if %errorlevel% neq 0 (
    echo Please run this batch file as administrator. The depencencies installation for Lumix requires administrator's permissions!
    goto :eof
)
move ".\src\cli\lumix.bat" "C:\Windows\System32\"
if %errorlevel% equ 0 (
    echo File moved successfully.
) else (
    echo Failed to move the file.
)
pause