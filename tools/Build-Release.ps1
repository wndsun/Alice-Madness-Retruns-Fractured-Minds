[CmdletBinding()]
param(
    [string]$Version = '1.0.0',
    [ValidateSet('Debug', 'Release')]
    [string]$Configuration = 'Release',
    [switch]$SkipBuild
)

# Builds AliceFracturedMinds and creates one release archive whose root is the
# game's Binaries\Win32 folder:
#   dinput8.dll, MadnessPatch.ini        next to AliceMadnessReturns.exe
#   AliceCoop\...                        server, settings, scripts, images, docs

$ErrorActionPreference = 'Stop'
$repoRoot = Split-Path -Parent $PSScriptRoot
$artifactsRoot = Join-Path $repoRoot 'artifacts'
$packageName = "AliceFracturedMinds-$Version"
$stagingPath = Join-Path $artifactsRoot $packageName
$archivePath = Join-Path $artifactsRoot "$packageName.zip"
$checksumPath = Join-Path $artifactsRoot "$packageName-SHA256SUMS.txt"
$coopPath = Join-Path $stagingPath 'AliceCoop'
$repositoryUrl = 'https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds'

if (-not $SkipBuild) {
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path -LiteralPath $vswhere -PathType Leaf)) {
        throw 'Visual Studio Installer (vswhere.exe) was not found.'
    }
    $msbuild = & $vswhere -latest -products * `
        -requires Microsoft.Component.MSBuild `
        -find 'MSBuild\**\Bin\MSBuild.exe' |
        Select-Object -First 1
    if (-not $msbuild) {
        throw 'MSBuild was not found.'
    }
    & $msbuild (Join-Path $repoRoot 'AliceCoop.sln') /m /t:Build `
        "/p:Configuration=$Configuration" /p:Platform=x86
    if ($LASTEXITCODE -ne 0) {
        throw "MSBuild failed with exit code $LASTEXITCODE."
    }
}

$buildPath = Join-Path $repoRoot "bin\$Configuration"
$builtDll = Join-Path $buildPath 'dinput8.dll'
$builtServer = Join-Path $buildPath 'AliceCoopServer.exe'
foreach ($requiredFile in @($builtDll, $builtServer)) {
    if (-not (Test-Path -LiteralPath $requiredFile -PathType Leaf)) {
        throw "Required build output is missing: $requiredFile"
    }
}

& $builtServer --self-test
if ($LASTEXITCODE -ne 0) {
    throw "AliceCoopServer self-test failed with exit code $LASTEXITCODE."
}

New-Item -ItemType Directory -Force -Path $artifactsRoot | Out-Null
foreach ($old in @($stagingPath, $archivePath, $checksumPath)) {
    if (Test-Path -LiteralPath $old) {
        Remove-Item -LiteralPath $old -Recurse -Force
    }
}
New-Item -ItemType Directory -Force -Path `
    $coopPath, (Join-Path $coopPath 'images'), (Join-Path $coopPath 'docs') | Out-Null

# Next to the game executable.
Copy-Item -LiteralPath $builtDll -Destination $stagingPath
Copy-Item -LiteralPath (Join-Path $repoRoot 'client\MadnessPatch.ini') -Destination $stagingPath

# AliceCoop folder.
Copy-Item -LiteralPath $builtServer -Destination $coopPath
Copy-Item -LiteralPath (Join-Path $repoRoot 'AliceCoop.ini') -Destination $coopPath
Get-ChildItem -LiteralPath (Join-Path $repoRoot 'manual-launch') -Filter '*.bat' |
    Copy-Item -Destination $coopPath
Get-ChildItem -LiteralPath (Join-Path $repoRoot 'images') -Filter '*.png' |
    Copy-Item -Destination (Join-Path $coopPath 'images')
foreach ($name in @('README.md', 'README_RU.md', 'CHANGELOG.md',
        'LICENSE', 'NOTICE.md', 'THIRD_PARTY_NOTICES.md')) {
    $source = Join-Path $repoRoot $name
    if (Test-Path -LiteralPath $source -PathType Leaf) {
        Copy-Item -LiteralPath $source -Destination $coopPath
    }
}
Get-ChildItem -LiteralPath (Join-Path $repoRoot 'docs') -Filter '*.md' |
    Where-Object Name -notin @('DEVELOPMENT.md', 'ARCHITECTURE.md') |
    Copy-Item -Destination (Join-Path $coopPath 'docs')
Copy-Item -LiteralPath (Join-Path $repoRoot 'third_party\licenses') `
    -Destination (Join-Path $coopPath 'third-party-licenses') -Recurse

$commit = (& git -C $repoRoot rev-parse --short HEAD 2>$null)
if (-not $commit) { $commit = 'unknown' }
@"
AliceFracturedMinds $Version - corresponding source code

Repository: $repositoryUrl
Release tag: $repositoryUrl/tree/v$Version
Source commit: $commit

AliceFracturedMinds is a fork of Alice Co-op by Docwitson
(https://github.com/docwitson/Alice-Madness-Returns-Co-op), built on
MadnessPatch by Wemino (https://github.com/Wemino/MadnessPatch).
It is distributed under the GNU General Public License version 2.0.
The tagged repository contains the source and build files that correspond
to the binaries in this archive.
"@ | Set-Content -LiteralPath (Join-Path $coopPath 'SOURCE_CODE.txt') -Encoding UTF8

Compress-Archive -Path (Join-Path $stagingPath '*') -DestinationPath $archivePath `
    -CompressionLevel Optimal

$archiveHash = (Get-FileHash -LiteralPath $archivePath -Algorithm SHA256).Hash
"$archiveHash  $([System.IO.Path]::GetFileName($archivePath))" |
    Set-Content -LiteralPath $checksumPath -Encoding ASCII

Write-Host ''
Write-Host "Release archive: $archivePath"
Write-Host "SHA256:          $archiveHash"
