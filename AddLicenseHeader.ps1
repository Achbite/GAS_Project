<#
.SYNOPSIS
Adds a license header to C++ source files (.h, .cpp) and Lua script files (.lua)
within specified directories. Skips files that already contain a copyright notice.

.DESCRIPTION
This script iterates through the specified source and script directories,
reads each file, checks if a copyright header (Copyright (C) YYYY) already exists
within the first few lines, and prepends the current year's header if it's missing.
It uses appropriate comment styles for C++ and Lua.

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
# Use dynamic year for the license text itself
$currentYear = Get-Date -Format yyyy
$cppLicenseText = @"
/* 
 * Copyright (C) $currentYear $CopyrightHolder
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
 -- Copyright (C) $currentYear $CopyrightHolder
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
        [string]$CopyrightRegexPattern = 'Copyright \(C\) \d{4}' # Regex to find any year
    )

    $writer = $null # Initialize writer variable outside try

    try {
        Write-Host "Processing: $FilePath" -ForegroundColor Cyan
        # Read only the first few lines for checking using UTF-8
        $linesToCheck = Get-Content -Path $FilePath -Encoding UTF8 -TotalCount 10 -ErrorAction Stop 
        $contentToCheck = $linesToCheck -join "`n" 

        # Check if license already exists using regex
        if ($contentToCheck -match $CopyrightRegexPattern) {
            Write-Host "  License header already exists. Skipping." -ForegroundColor Gray
            return
        }

        # If no license found, read the full content using UTF-8
        $fullContent = Get-Content -Path $FilePath -Raw -Encoding UTF8 -ErrorAction Stop
        $newContent = $LicenseText + "`r`n" + $fullContent 

        # Write back to file using UTF-8 without BOM via StreamWriter
        $utf8NoBomEncoding = New-Object System.Text.UTF8Encoding($false) # $false specifies no BOM
        
        # Create StreamWriter with the specified encoding
        $writer = New-Object System.IO.StreamWriter($FilePath, $false, $utf8NoBomEncoding) # $false for overwrite
        $writer.Write($newContent) 
        
        # [System.IO.File]::WriteAllText($FilePath, $newContent, $utf8NoBomEncoding) # Replaced this line
        Write-Host "  License header added (UTF-8 without BOM)." -ForegroundColor Green

    } catch {
        Write-Error "Error processing file '$FilePath': $_"
    } finally {
        # Ensure the writer is closed and disposed even if errors occur
        if ($writer -ne $null) {
            $writer.Close()
            $writer.Dispose()
        }
    }
}

# --- Process C++ Files ---
$cppFiles = Get-ChildItem -Path $CppSourceDir -Recurse -Include *.h, *.cpp
# No need for cppCopyrightCheck string anymore, using regex by default

Write-Host "--- Processing C++ Files in '$CppSourceDir' ---" -ForegroundColor Yellow
foreach ($file in $cppFiles) {
    # Pass the dynamically generated C++ license text
    Add-LicenseHeaderToFile -FilePath $file.FullName -LicenseText $cppLicenseText 
}

# --- Process Lua Files ---
# Check if Lua directory exists before processing
if (Test-Path $LuaScriptDir -PathType Container) {
    $luaFiles = Get-ChildItem -Path $LuaScriptDir -Recurse -Include *.lua
    # No need for luaCopyrightCheck string anymore, using regex by default

    Write-Host "--- Processing Lua Files in '$LuaScriptDir' ---" -ForegroundColor Yellow
    foreach ($file in $luaFiles) {
        # Pass the dynamically generated Lua license text
        Add-LicenseHeaderToFile -FilePath $file.FullName -LicenseText $luaLicenseText
    }
} else {
    Write-Warning "Lua script directory '$LuaScriptDir' not found. Skipping Lua file processing."
}

Write-Host "--- Script Finished ---" -ForegroundColor Yellow
