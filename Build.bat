@echo off
chcp 65001 >nul
title Build Chess
echo ========================================
echo      CHESS - Build from Source
echo ========================================
echo.

:: Get the directory where this batch file is located
set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%"

:: Check if CMake is installed
where cmake >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake not found!
    echo.
    echo Please install CMake:
    echo https://cmake.org/download/
    echo.
    pause
    exit /b 1
)

:: Check if g++ is installed
where g++ >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ERROR: g++ compiler not found!
    echo.
    echo Please install MSYS2:
    echo https://www.msys2.org/
    echo.
    pause
    exit /b 1
)

echo [1/3] Cleaning old build...
if exist "build" (
    rmdir /s /q "build"
)
mkdir build
cd build

echo [2/3] Configuring with CMake...
cmake -G "MinGW Makefiles" ..
if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: CMake configuration failed!
    echo.
    pause
    exit /b 1
)

echo [3/3] Building...
cmake --build . -- -j
if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Build failed!
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo      BUILD SUCCESSFUL!
echo ========================================
echo.
echo To run the game:
echo   cd build
echo   .\Chess.exe
echo.
echo Or double-click: build\Chess.exe
echo.

:: Ask if they want to run the game
set /p RUN="Run Chess now? (Y/N): "
if /i "%RUN%"=="Y" (
    start "" "Chess.exe"
)

pause