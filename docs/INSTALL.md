# Installation and update

## Requirements

- A legitimate PC copy of *Alice: Madness Returns* (Steam or EA App) on both PCs.
- Windows 10 or 11. The game and the mod are 32-bit.
- Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- The same AliceFracturedMinds release on both PCs.
- Localhost, a trusted LAN, or a trusted VPN such as Radmin VPN.

The mod's `dinput8.dll` already contains MadnessPatch 3.1.1 - do not install
MadnessPatch separately.

## Game folder

The mod goes into the folder that contains `AliceMadnessReturns.exe`:

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <EA folder>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## Install

1. Close the game.
2. Back up your saves and, if present, your own `dinput8.dll` and
   `MadnessPatch.ini` - the archive replaces them.
3. Extract `AliceFracturedMinds-<version>.zip` into `Binaries\Win32`, keeping
   the folder structure. You should get:

   ```text
   AliceMadnessReturns.exe
   dinput8.dll
   MadnessPatch.ini
   AliceCoop\AliceCoopServer.exe
   AliceCoop\AliceCoop.ini
   AliceCoop\images\...
   ```

4. If the game closes before its window appears, install the Visual C++
   Redistributable x86.

## Playing

1. Both players start the game normally (Steam / EA App).
2. Press `M` to open the menu:
   - **Host**: choose *Host*, keep `127.0.0.1` and press *Save* - the relay
     server starts on the host PC.
   - **Client**: choose *Client*, enter the host's LAN/VPN address and the same
     port, press *Save*.
3. The role is applied the next time the game starts - restart the game after
   changing it. Address and port apply immediately.
4. The host loads a save and enters gameplay. The client presses `L` in the main
   menu or in gameplay to join the host's checkpoint.

The host must allow inbound UDP on the port (default `27018`) in Windows
Firewall. Never forward this port to the Internet.

Instead of the menu you can use the scripts in the `AliceCoop` folder:
`AliceCoop-Host.bat`, `AliceCoop-Client.bat [server-ip] [port]` and
`AliceCoop-Server.bat`. On Steam the game may restart itself through the Steam
client and lose the settings passed by a script - then use `AliceCoop.ini` or
the `M` menu.

## Update

1. Close the game and the server on both PCs.
2. Keep a copy of your `AliceCoop\AliceCoop.ini` and `MadnessPatch.ini`.
3. Extract the new archive over the old files and re-apply your settings.
4. Read the [changelog](../CHANGELOG.md) for new settings.

## Uninstall

Delete `dinput8.dll`, `MadnessPatch.ini` and the `AliceCoop` folder from
`Binaries\Win32`. Saves made by the client in co-op are in
`AliceCoop\client-saves`. No original game file is changed by the mod.
