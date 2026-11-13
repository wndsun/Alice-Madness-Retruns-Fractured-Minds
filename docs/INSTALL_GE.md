# Installation und Aktualisierung

## Voraussetzungen

- Eine legale PC-Version von *Alice: Madness Returns* (Steam oder EA App) auf beiden PCs.
- Windows 10 oder 11. Das Spiel und die Mod sind 32-Bit-Anwendungen.
- Microsoft Visual C++ 2015–2022 Redistributable **x86**.
- Auf beiden PCs muss dieselbe Version von AliceFracturedMinds installiert sein.
- Localhost, ein vertrauenswürdiges lokales Netzwerk (LAN) oder ein vertrauenswürdiges VPN, beispielsweise Radmin VPN.

Die `dinput8.dll` der Mod enthält bereits MadnessPatch 3.1.1. MadnessPatch muss daher nicht separat installiert werden.

## Spielverzeichnis

Die Mod muss in dem Ordner installiert werden, der die Datei `AliceMadnessReturns.exe` enthält:

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <EA-Ordner>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## Installation

1. Beende das Spiel.
2. Erstelle eine Sicherungskopie deiner Spielstände sowie deiner eigenen Dateien `dinput8.dll` und `MadnessPatch.ini`, falls diese vorhanden sind. Das Archiv wird diese Dateien ersetzen.
3. Entpacke `AliceFracturedMinds-<version>.zip` in den Ordner `Binaries\Win32`, ohne die Ordnerstruktur zu verändern. Anschließend sollten folgende Dateien vorhanden sein:

```text
AliceMadnessReturns.exe
dinput8.dll
MadnessPatch.ini
AliceCoop\AliceCoopServer.exe
AliceCoop\AliceCoop.ini
AliceCoop\images\...
```

4. Falls sich das Spiel schließt, bevor das Spielfenster erscheint, installiere Visual C++ Redistributable x86.

## Koop-Modus

1. Beide Spieler starten das Spiel wie gewohnt (über Steam oder EA App).
2. Drücke die Taste `M`, um das Menü zu öffnen:

   - **Host (Gastgeber):** Wähle *Host*, lasse die Adresse `127.0.0.1` unverändert und drücke *Save*. Der Relay-Server wird auf dem PC des Gastgebers gestartet.
   - **Client:** Wähle *Client*, gib die LAN-/VPN-Adresse des Gastgebers sowie denselben Port ein und drücke anschließend *Save*.

3. Die ausgewählte Rolle wird beim nächsten Spielstart übernommen. Wenn du die Rolle änderst, musst du das Spiel neu starten. Adresse und Port werden sofort übernommen.
4. Der Gastgeber lädt einen Spielstand und startet das Spielgeschehen. Der Client drückt im Hauptmenü oder während des Spiels die Taste `L`, um dem Kontrollpunkt des Gastgebers beizutreten.

Der Gastgeber muss eingehende UDP-Verbindungen über den verwendeten Port (standardmäßig `27018`) in der Windows-Firewall zulassen.

**Leite diesen Port niemals ins Internet weiter.**

Alternativ zum Menü kannst du die Skripte im Ordner `AliceCoop` verwenden:

- `AliceCoop-Host.bat`
- `AliceCoop-Client.bat [server-ip] [port]`
- `AliceCoop-Server.bat`

Bei der Steam-Version kann es vorkommen, dass das Spiel automatisch über den Steam-Client neu gestartet wird und dabei die über ein Skript übergebenen Einstellungen verloren gehen. Verwende in diesem Fall `AliceCoop.ini` oder das Menü, das du mit der Taste `M` öffnen kannst.

## Aktualisierung

1. Beende das Spiel und den Server auf beiden PCs.
2. Erstelle eine Kopie der Dateien `AliceCoop\AliceCoop.ini` und `MadnessPatch.ini`.
3. Entpacke das neue Archiv über die vorhandenen Dateien und übernimm deine Einstellungen erneut.
4. Lies das [Änderungsprotokoll](../CHANGELOG.md), um dich über neue Einstellungen zu informieren.

## Deinstallation

Lösche die Dateien `dinput8.dll`, `MadnessPatch.ini` sowie den Ordner `AliceCoop` aus dem Verzeichnis `Binaries\Win32`.

Spielstände, die vom Client während des Koop-Modus erstellt wurden, befinden sich im Ordner `AliceCoop\client-saves`.

Die Mod verändert keine Originaldateien des Spiels.