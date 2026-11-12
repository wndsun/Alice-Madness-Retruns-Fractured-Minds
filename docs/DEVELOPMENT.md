# Development and release

## Toolchain

- Visual Studio 2022 or newer with *Desktop development with C++*
- MSVC v143 x86 tools and a Windows 10/11 SDK
- PowerShell 5.1 or later

Build:

```powershell
msbuild .\AliceCoop.sln /m /t:Build "/p:Configuration=Release;Platform=x86"
```

Outputs:

```text
bin\Release\dinput8.dll
bin\Release\AliceCoopServer.exe
```

Relay self-test:

```powershell
.\bin\Release\AliceCoopServer.exe --self-test
```

## Release archive

```powershell
.\tools\Build-Release.ps1 -Version 1.0.0
```

The script builds `Release|x86`, runs the server self-test and creates
`artifacts\AliceFracturedMinds-<version>.zip` (its root is the game's
`Binaries\Win32` folder) and a SHA-256 file. Pushing a tag `v<version>` runs the
same script on GitHub Actions and creates a draft release with the archive.

## Source layout

| Path | Purpose |
| --- | --- |
| `client/` | Combined MadnessPatch / co-op DLL project and default `MadnessPatch.ini` |
| `server/` | Standalone UDP relay (`AliceCoopServer.exe`) |
| `src/Coop/` | Protocol, remote Alice, shared world and lifecycle synchronization |
| `src/` | MadnessPatch base and shared hooks/features |
| `include/` | Project headers (in-game menu: `AchievementOverlay.hpp`), vendored libraries, UE3 SDK declarations |
| `lib/` | Vendored x86 static libraries |
| `manual-launch/` | Host / client / server launch scripts |
| `images/` | Images used by the in-game overlay |
| `tools/` | Release packaging |

## Release checklist

- Build from a clean tree and run the server self-test.
- Bump `Version` in `src/Coop/Protocol.hpp` when the protocol changes.
- Make sure `AliceCoop.ini` ships with all `[Trace]`, `HairRecord`,
  `EnemyRecord` and `Dumps` set to `0`.
- Test a clean install, host and client.
- Update `CHANGELOG.md`, create the tag, review the draft release and publish.
