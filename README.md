# AliceFracturedMinds

Two-player co-op for the PC version of *Alice: Madness Returns*.

Based on / fork of [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op)
by Docwitson, built on [MadnessPatch](https://github.com/Wemino/MadnessPatch).

[Русская версия](README_RU.md) · [Installation](docs/INSTALL.md) ·
[Configuration](docs/CONFIGURATION.md) · [Known issues](docs/KNOWN_ISSUES.md) ·
[Changelog](CHANGELOG.md) · [GPL-2.0](LICENSE)

Each player runs their own copy of the game. A small UDP relay
(`AliceCoopServer.exe`) exchanges player, animation and world state, and the
host is authoritative for enemies.

## Requirements

- A legitimate PC copy of the game (Steam or EA App) for each player.
- Windows 10/11 and the Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- The same AliceFracturedMinds release on both PCs.
- The same PC, a LAN, or a trusted VPN such as Radmin VPN.

## Quick start

1. Download `AliceFracturedMinds-<version>.zip` from
   [Releases](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/releases).
2. Extract it into `<game>\Binaries\Win32` (the folder with
   `AliceMadnessReturns.exe`).
3. Start the game, press `M`:
   - host: *Host*, *Save* (starts the relay server);
   - client: *Client*, the host's address, *Save*.
4. Restart the game after changing the role. The host enters gameplay, the
   client presses `L` to join.

Full guide: [docs/INSTALL.md](docs/INSTALL.md).

## Controls

| Key | Where | Action |
| --- | --- | --- |
| `M` | Anywhere | Open the co-op menu |
| `L` | Client / yellow action | Join the host, or force a waiting cutscene |
| `P` | Gameplay | Teleport to the other player (safe) |
| `O` | Client gameplay | Forced teleport to the host |
| `K` | Client main menu | Copy the host's save progress (overwrites the client profile) |
| `T` | Pause menu | Toggle the remote Alice's movement trails |

## Network warning

The relay has no authentication or encryption. Use it only on your PC, a LAN or
a trusted VPN, and never forward its port to the Internet.

## License

GPL-2.0 - see [LICENSE](LICENSE), [NOTICE.md](NOTICE.md) and
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md). Not affiliated with Electronic
Arts or Spicy Horse; no game files are included.
