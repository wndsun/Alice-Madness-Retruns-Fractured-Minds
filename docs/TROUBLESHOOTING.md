# Troubleshooting

## The game does not start

- The mod must be in the folder with `AliceMadnessReturns.exe` (`Binaries\Win32`).
- Install Microsoft Visual C++ Redistributable 2015-2022 **x86**.
- Remove other `dinput8.dll` mods - only one file with that name can be loaded.

## The other player stays offline

- Both players need the same release, the same port and the host's reachable
  address (`127.0.0.1` only when the server runs on the same PC).
- Only one relay server must run. The host starts it with *Save* in the `M`
  menu or with `AliceCoop-Server.bat`.
- Allow `AliceCoopServer.exe` through Windows Firewall for private networks.
- With a VPN, check that both PCs are in the same VPN network and can ping each
  other.

## The role is wrong

The role is read when the game starts. After changing it in the `M` menu,
restart the game.

## Join does nothing

- Wait until the host is fully in gameplay and not loading a map or playing a
  cutscene, then press `L` again.

## Client loaded far away

Wait until the level is ready and the client can move, then press `O`. Use `P`
during normal play in the same area.

## A cutscene is waiting forever

Bring both players into the trigger area. If both are there, press `L` while the
yellow action is visible. Restart the checkpoint if the world state looks wrong
afterwards.

## The game crashed

Send `AliceCoop\logs\AliceCoop_host_*.log` / `AliceCoop_client_*.log` and the
`crash_*.txt` file from the game folder, after removing personal information.
