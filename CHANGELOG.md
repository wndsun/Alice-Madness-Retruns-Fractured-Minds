# Changelog

All notable user-facing changes are listed here. Both players must use the same
release: the network protocol version is shown in the log at start-up.

## 1.0.0 - unreleased

First release of AliceFracturedMinds, a fork of Alice Co-op 0.1.0-alpha.1.

### Added

- In-game menu (`M`): role (host/client), server address and port, saved to
  `AliceCoop.ini`; the host can start the relay server from the menu.
- Watching the host in the real-world (London) chapters.
- Synchronized Executioner chase: shared hits, knockback, laugh and end of chase.
- Shared enemy spawns after death, restart and Continue.
- `AliceCoop.ini` switches: `[General] GameConsole`, `[Debug] Logs`,
  `[Debug] Dumps`.

### Changed

- Normal launch through Steam or the EA App works without the external launcher
  (`EnableWithoutLauncher = 1` by default).
- The launch scripts no longer need `AliceCoop-LaunchConfig.bat`: settings come
  from `AliceCoop.ini`.
- One release archive that is extracted into `Binaries\Win32`.

### Fixed

- Many crashes during respawn, map changes and enemy teardown.
- Cloned enemies after Continue, cutscene-skip desync, Elite Card Guard
  encounters and checkpoint mismatches when continuing from the main menu.

### Removed

- External launcher, installer and uninstaller scripts.
- Local test scripts (`AliceCoop-Both.bat`, `AliceCoop-Animation-Test.bat`,
  `AliceCoop-Diagnostic-Both.bat`).

## Alice Co-op 0.1.0-alpha.1 - 2026-08-27 (upstream)

The original release by Docwitson that this fork is based on. See
[the upstream repository](https://github.com/docwitson/Alice-Madness-Returns-Co-op).
