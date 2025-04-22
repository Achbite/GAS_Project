<#
.SYNOPSIS
Adds a license header to C++ source files (.h, .cpp) and Lua script files (.lua)
within specified directories.

.DESCRIPTION
This script iterates through the specified source and script directories,
reads each file, checks if the license header already exists, and prepends
the header if it's missing. It uses appropriate comment styles for C++ and Lua.

.PARAMETER CppSourceDir
The root directory containing C++ source files (.h, .cpp).

.PARAMETER LuaScriptDir
The root directory containing Lua script files (.lua).

.PARAMETER CopyrightHolder
The name of the copyright holder (e.g., "Your Name or Company").

.EXAMPLE
.\AddLicenseHeader.ps1 -CopyrightHolder "My Company"

.NOTES
- Always back up your project before running this script.
- Ensure the paths in the script match your project structure.
- The script assumes UTF-8 encoding for files.
#>
param(
    [string]$CppSourceDir = "c:\Users\Administrator\Desktop\AnabiosisOrigin\Source",
    [string]$LuaScriptDir = "c:\Users\Administrator\Desktop\AnabiosisOrigin\Script", # Adjust if your Lua scripts are elsewhere (e.g., Plugins/UnLua/Content/Script)
    [string]$CopyrightHolder = "[Wang]" # !!! REPLACE THIS WITH THE ACTUAL COPYRIGHT HOLDER !!!
)

# --- License Text ---
$cppLicenseText = @"
/* 
 * Copyright (C) $(Get-Date -Format yyyy) $CopyrightHolder
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see https://www.gnu.org/licenses/. 
 */
"@

$luaLicenseText = @"
--[[ 
 -- Copyright (C) $(Get-Date -Format yyyy) $CopyrightHolder
 -- 
 -- This program is free software: you can redistribute it and/or modify 
 -- it under the terms of the GNU General Public License as published by 
 -- the Free Software Foundation, either version 3 of the License, or 
 -- (at any later version. 
 -- 
 -- This program is distributed in the hope that it will be useful, 
 -- but WITHOUT ANY WARRANTY; without even the implied warranty of 
 -- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 -- GNU General Public License for more details. 
 -- 
 -- You should have received a copy of the GNU General Public License 
 -- along with this program.  If not, see https://www.gnu.org/licenses/. 
 --]]
"@

# --- Function to process files ---
function Add-LicenseHeaderToFile {
    param(
        [string]$FilePath,
        [string]$LicenseText,
        [string]$CopyrightCheckString
    )

    try {
        Write-Host "Processing: $FilePath" -ForegroundColor Cyan
        $content = Get-Content -Path $FilePath -Raw -Encoding UTF8 -ErrorAction Stop
        $firstLine = ($content -split '\r?\n')[0] # Get the first line for check

        # Check if license already exists (simple check on the first few lines)
        if ($content.StartsWith($CopyrightCheckString) -or $firstLine.Contains($CopyrightCheckString)) {
            Write-Host "  License header already exists. Skipping." -ForegroundColor Gray
            return
        }

        # Prepend license
        $newContent = $LicenseText + "`r`n" + $content # Use CRLF for consistency, adjust if needed
        
        # Write back to file
        Set-Content -Path $FilePath -Value $newContent -Encoding UTF8 -Force -ErrorAction Stop
        Write-Host "  License header added." -ForegroundColor Green

    } catch {
        Write-Error "Error processing file '$FilePath': $_"
    }
}

# --- Process C++ Files ---
$cppFiles = Get-ChildItem -Path $CppSourceDir -Recurse -Include *.h, *.cpp
$cppCopyrightCheck = "Copyright (C) $(Get-Date -Format yyyy) $CopyrightHolder" # String to check for existence

Write-Host "--- Processing C++ Files in '$CppSourceDir' ---" -ForegroundColor Yellow
foreach ($file in $cppFiles) {
    Add-LicenseHeaderToFile -FilePath $file.FullName -LicenseText $cppLicenseText -CopyrightCheckString $cppCopyrightCheck
}

# --- Process Lua Files ---
# Check if Lua directory exists before processing
if (Test-Path $LuaScriptDir -PathType Container) {
    $luaFiles = Get-ChildItem -Path $LuaScriptDir -Recurse -Include *.lua
    $luaCopyrightCheck = "Copyright (C) $(Get-Date -Format yyyy) $CopyrightHolder" # String to check for existence

    Write-Host "--- Processing Lua Files in '$LuaScriptDir' ---" -ForegroundColor Yellow
    foreach ($file in $luaFiles) {
        Add-LicenseHeaderToFile -FilePath $file.FullName -LicenseText $luaLicenseText -CopyrightCheckString $luaCopyrightCheck
    }
} else {
    Write-Warning "Lua script directory '$LuaScriptDir' not found. Skipping Lua file processing."
}


Write-Host "--- Script Finished ---" -ForegroundColor Yellow
