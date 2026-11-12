# Configuration reference

## In-game menu (`M`)

Role, server address and port. *Save* writes them to `AliceCoop.ini`; the
address and port apply immediately, the role on the next game start. Saving as
*Host* starts `AliceCoopServer.exe` hidden; saving as *Client* stops it.

## AliceCoop.ini

`<game>\Binaries\Win32\AliceCoop\AliceCoop.ini`. The shipped values are the
tested defaults - change only what you need.

| Section | Key | Default | Description |
| --- | --- | --- | --- |
| `[Network]` | `EnableWithoutLauncher` | `1` | Co-op is active when the game starts normally |
| | `Role` | `host` | `host` or `client` |
| | `ServerAddress` | `127.0.0.1` | Address of the PC running the relay server |
| | `Port` | `27018` | UDP port, the same for everyone |
| `[VisualProxy]` | `Enabled` | `1` | Show the other player's Alice |
| | `PreserveMovementTrails` | `0` | Cosmetic glide/jump particle history (`T` in the pause menu) |
| `[SharedWorld]` | `EnemyHealth`, `EnemyTransforms` | `1` | Host-authoritative enemies |
| `[Performance]` | `MaxFPS` | `60` | FPS limit (30-120) |
| | `LowMemoryMode` | `1` | Lighter textures for two 32-bit game processes |
| `[General]` | `GameConsole` | not set | `0` / `1` turns the F2 console off / on; not set = `EnableConsole` in `MadnessPatch.ini` |
| `[Debug]` | `Logs` | `0` | `1` writes logs to `AliceCoop\logs` (needed for bug reports); `0` disables every file the mod writes |
| | `DiagTrail` | `1` | Short action trail saved with a crash report (only with `Logs = 1`) |
| | `Dumps` | `0` | Developer research dumps - keep `0` |
| | `HairRecord`, `EnemyRecord` | `0` | Large developer recordings - keep `0` |

`[Trace]` options are developer diagnostics; keep them all at `0`. The other
`[VisualProxy]` and `[Debug]` keys are tuned values - leave them as shipped.

## Launch scripts

The scripts in `AliceCoop\` read `AliceCoop.ini` and accept optional
overrides:

```text
AliceCoop-Host.bat
AliceCoop-Client.bat 26.x.x.x 27018
AliceCoop-Server.bat 0.0.0.0 27018
```

## MadnessPatch.ini

The combined DLL reads the normal MadnessPatch settings next to
`AliceMadnessReturns.exe`. Keep `CrashFixes`, the high-FPS physics fixes, atomic
saves and the input fixes enabled.
