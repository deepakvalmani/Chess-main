@echo off
chcp 65001 >nul
title Chess Game
echo ========================================
echo      CHESS - Click to Play
echo ========================================
echo.
echo Starting game...
echo.

:: Get the directory where this batch file is located
set "SCRIPT_DIR=%~dp0"

:: Change to the script directory
cd /d "%SCRIPT_DIR%"

:: Check if Chess.exe exists
if not exist "Chess.exe" (
    echo ERROR: Chess.exe not found!
    echo.
    echo Please make sure all files are in the same folder.
    echo.
    pause
    exit /b 1
)

:: Check if assets folder exists
if not exist "assets" (
    echo WARNING: assets folder not found!
    echo Some game features may not work.
    echo.
)

:: Run the game
start "" "Chess.exe"

:: Wait a moment for the game to start
timeout /t 2 /nobreak >nul

echo Game should be running now!
echo.
echo If the game didn't start, try:
echo 1. Right-click this file and select "Run as administrator"
echo 2. Or double-click Chess.exe directly
echo.
pause