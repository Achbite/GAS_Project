@echo off
REM Executes the AddLicenseHeader.ps1 script using PowerShell, bypassing execution policy for this run.
powershell.exe -ExecutionPolicy Bypass -File "%~dp0AddLicenseHeader.ps1"

REM Optional: Pause to see the output before the window closes. Remove if not needed.
pause
