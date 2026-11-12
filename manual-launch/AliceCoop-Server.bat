@echo off
setlocal
rem AliceFracturedMinds relay server. Start it on ONE PC only.
rem The host can also start it from the in-game M menu instead.
rem The port is read from AliceCoop.ini [Network] Port. Optional overrides:
rem   AliceCoop-Server.bat [bind-ip] [port]

for %%I in ("%~dp0.") do set "COOP_DIR=%%~fI"
set "SERVER_EXE=%COOP_DIR%\AliceCoopServer.exe"
if not exist "%SERVER_EXE%" (
    echo ERROR: AliceCoopServer.exe was not found in:
    echo %COOP_DIR%
    pause
    exit /b 1
)

set "BIND_IP=0.0.0.0"
set "COOP_PORT=27018"
if exist "%COOP_DIR%\AliceCoop.ini" (
    for /f "tokens=1,* delims==" %%A in ('findstr /b /i /r /c:"Port *=" "%COOP_DIR%\AliceCoop.ini"') do set "COOP_PORT=%%B"
)
set "COOP_PORT=%COOP_PORT: =%"
if not "%~1"=="" set "BIND_IP=%~1"
if not "%~2"=="" set "COOP_PORT=%~2"

cd /d "%COOP_DIR%"
echo AliceFracturedMinds relay server
echo Listening on %BIND_IP%:%COOP_PORT% (UDP)
echo Close this window or press Ctrl+C to stop the server.
echo.

"%SERVER_EXE%" --bind "%BIND_IP%" --port "%COOP_PORT%" --log-dir "%COOP_DIR%\logs"

echo.
echo Server stopped with exit code %ERRORLEVEL%.
pause
