@echo off
echo ===================================================
echo   Running Unreal Engine 5.4 Automation Suite
echo ===================================================

set ENGINE_PATH="C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat"
set PROJECT_PATH="D:\Unreal_Engine_Automation\Automation_Lab\Automation_Lab.uproject"
set REPORT_PATH="D:\Unreal_Engine_Automation\Automation_Lab\Saved\Automation\Reports"

if not exist %REPORT_PATH% mkdir %REPORT_PATH%

call %ENGINE_PATH% BuildCookRun -project=%PROJECT_PATH% -build -compile -run -ExecCmds="Automation RunTests AutomationLab; Quit" -unattended -nullrhi -log -stdout

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Automation tests failed with code %ERRORLEVEL%!
    exit /b %ERRORLEVEL%
)

:: 1. Copiar log completo
copy /Y "%APPDATA%\Unreal Engine\AutomationTool\Logs\C+Program+Files+Epic+Games+UE_5.4\Client.log" "%REPORT_PATH%\AutomationTestResults.log" >nul

:: 2. Generar index.html extrayendo las lineas clave de ejecucion
powershell -Command "$log = Get-Content '%REPORT_PATH%\AutomationTestResults.log'; $filtered = $log | Select-String -Pattern 'AutomationLab', 'LogAutomation', 'Executing', 'Test', 'Passed', 'Failed' | Out-String; if ([string]::IsNullOrWhiteSpace($filtered)) { $filtered = 'No matched test lines found. Check raw log.' }; $html = '<html><head><title>UE5 Test Report</title><style>body{font-family:sans-serif;background:#1e1e1e;color:#ddd;padding:20px;} pre{background:#2d2d2d;padding:15px;border-radius:5px;overflow-x:auto;color:#4EC9B0;} .success{color:#4EC9B0;}</style></head><body><h1 class=\"success\">Automation Test Report - SUCCESS</h1><hr><h3>Execution Summary Log:</h3><pre>' + $filtered + '</pre></body></html>'; Set-Content -Path '%REPORT_PATH%\index.html' -Value $html"

echo.
echo [SUCCESS] Report generated! Check Saved\Automation\Reports\index.html
exit /b 0