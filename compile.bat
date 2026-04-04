:; # ── Shell section (Linux / macOS) ──────────────────────────────
:; PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
:; cd "$PROJECT_DIR"
:; if command -v cl &>/dev/null; then
:;   cl /std:c++latest /EHsc /nologo /W4 /MTd src/account.cpp src/ATM.cpp src/main.cpp /Fe:VirtualBank.exe
:; elif command -v g++ &>/dev/null; then
:;   echo "Using g++..."
:;   g++ -std=c++23 -Wall -o VirtualBank src/account.cpp src/ATM.cpp src/main.cpp
:; elif command -v clang++ &>/dev/null; then
:;   echo "Using clang++..."
:;   clang++ -std=c++23 -Wall -o VirtualBank src/account.cpp src/ATM.cpp src/main.cpp
:; else
:;   echo "No compiler found. Install g++ or clang++ compiler."
:;   exit 1
:; fi
:; exit 0

@echo off
:: ── Batch section (Windows) ───────────────────────────────────────
set "PROJECT_DIR=%~dp0"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VS_PATH=%%i"
)

if defined VS_PATH (
    echo Using MSVC...
    cmd /k ""%VS_PATH%\Common7\Tools\VsDevCmd.bat" && cd /d "%PROJECT_DIR%" && cl /std:c++latest /EHsc /nologo /W4 /MTd src\account.cpp src\ATM.cpp src\main.cpp /Fe:VirtualBank.exe && del account.obj ATM.obj main.obj"
    goto :eof
)

where g++ >nul 2>&1
if %errorlevel%==0 (
    echo MSVC not found, using g++...
    cmd /k "cd /d "%PROJECT_DIR%" && g++ -std=c++23 -Wall -o VirtualBank src/account.cpp src/ATM.cpp src/main.cpp && del account.obj ATM.obj main.obj"
    goto :eof
)

echo No compiler found. Install Visual Studio or g++ compiler.
pause
