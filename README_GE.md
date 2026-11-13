# Alice Madness Returns Fractured Minds

<p align="center">
  <img src="docs/media//spl01.png" width="1000" alt="AliceFracturedMinds">
</p>

Kooperativer Spielmodus für zwei Spieler in der PC-Version von *Alice: Madness Returns*.

Basiert auf / ist ein Fork von [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op) von Docwitson und wurde auf Grundlage von [MadnessPatch](https://github.com/Wemino/MadnessPatch) entwickelt.

### Download

**`AliceFracturedMinds-1.0.0.zip`** – Entpacke das Archiv in den Ordner `<game>\Binaries\Win32` (den Ordner, in dem sich `AliceMadnessReturns.exe` befindet). Beide Spieler müssen dieselbe Version verwenden.

### Schnellstart

1. Starte das Spiel wie gewohnt (über Steam / EA App) und drücke **M**.
2. Host: Wähle *Host* → *Save* (dadurch wird der Relay-Server gestartet).
   Client: Wähle *Client*, gib die LAN-/VPN-Adresse des Hosts ein und wähle *Save*.
3. Starte das Spiel neu, nachdem du die Rolle geändert hast. Der Host startet das Spiel, während der Client **L** drückt, um beizutreten.

Vollständige Anleitung: [docs/INSTALL.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/docs/INSTALL.md)

### Neuerungen gegenüber Alice Co-op 0.1.0-alpha.1

- Koop-Menü direkt im Spiel (**M**): Einstellung der Rolle, Serveradresse und des Ports. Der Host kann den Server direkt über das Menü starten. Ein externer Launcher ist nicht erforderlich.
- Möglichkeit, den Host während der London-Kapitel zu beobachten.
- Synchronisierte Verfolgungsjagd mit dem Henker: Treffer, Rückstoß, Lachen und Ende der Verfolgungsjagd.
- Gemeinsames Erscheinen von Gegnern nach dem Tod, einem Neustart und dem Fortsetzen des Spiels.
- Zahlreiche Absturzkorrekturen (Respawn, Kartenwechsel und Entfernen von Gegnern).
- Fehler mit duplizierten Gegnern nach dem Fortsetzen des Spiels, Synchronisationsprobleme beim Überspringen von Zwischensequenzen, Begegnungen mit Elite Card Guard sowie Abweichungen bei Checkpoints nach dem Fortsetzen über das Hauptmenü wurden behoben.
- Neue Optionen in `AliceCoop.ini`: `GameConsole`, `Logs`, `Dumps`.

Vollständige Änderungsliste: [CHANGELOG.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/CHANGELOG.md)

### Systemanforderungen

- Jeder Spieler benötigt eine legitime PC-Version des Spiels (Steam oder EA App). Spieldateien sind nicht enthalten.
- Windows 10/11, Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- Derselbe PC, ein lokales Netzwerk (LAN) oder ein vertrauenswürdiges VPN (z. B. Radmin VPN).

> [!WARNING]
> Der Relay-Server verfügt weder über Authentifizierung noch über Verschlüsselung. Leite seinen Port (UDP 27018) niemals ins Internet weiter.
>
> Das Archiv ersetzt `dinput8.dll` und `MadnessPatch.ini`. Erstelle Sicherungskopien dieser Dateien sowie deiner Spielstände.

### Fehler melden

Die Protokollierung (Logs) ist standardmäßig deaktiviert. Setze `Logs = 1` im Abschnitt `[Debug]` der Datei `AliceCoop\AliceCoop.ini`, reproduziere das Problem und füge die Dateien aus dem Ordner `AliceCoop\logs` zu einem [Fehlerbericht (Issue)](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/issues) hinzu.