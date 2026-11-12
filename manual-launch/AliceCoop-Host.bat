@echo off
setlocal
rem AliceFracturedMinds - start the game as HOST.
rem Server address and port come from AliceCoop.ini [Network]
rem (or the in-game M menu). Optional overrides:
rem   AliceCoop-Host.bat <server-ip> [port]

for %%I in ("%~dp0.") do set "COOP_DIR=%%~fI"

set "ALICECOOP_ENABLE=1"
set "ALICECOOP_ROLE=host"
if not "%~1"=="" set "ALICECOOP_SERVER=%~1"
if not "%~2"=="" set "ALICECOOP_PORT=%~2"

for %%I in ("%COOP_DIR%\..") do set "GAME_DIR=%%~fI"
set "GAME_EXE=%GAME_DIR%\AliceMadnessReturns.exe"
if not exist "%GAME_EXE%" (
    echo ERROR: AliceMadnessReturns.exe was not found in:
    echo %GAME_DIR%
    echo The AliceCoop folder must be inside Binaries\Win32 of the game.
    pause
    exit /b 1
)

echo Starting AliceFracturedMinds HOST...
start "AliceFracturedMinds HOST" /D "%GAME_DIR%" "%GAME_EXE%"
