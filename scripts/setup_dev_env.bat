@echo off
setlocal

:: get the path to the current script
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%.."

:: clone vcpkg
echo Cloning https://github.com/microsoft/vcpkg.git
git clone https://github.com/microsoft/vcpkg.git
if errorlevel 1 (
    echo Failed to clone vcpkg
    exit /b 1
)

:: cd vcpkg
cd vcpkg

:: build vcpkg
echo bootstrap-vcpkg.bat...
call bootstrap-vcpkg.bat
if errorlevel 1 (
    echo Failed to bootstrap vcpkg
    exit /b 1
)

.\vcpkg install spdlog:x64-windows
if errorlevel 1 (
    echo Failed to install spdlog
    exit /b 1
)

:: return to the project root
cd ..

:: echo setup complete
echo Setup complete. When running cmake, use the following command:
echo cmake -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake

endlocal