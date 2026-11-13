# Installazione e aggiornamento

## Requisiti

- Una copia legittima di *Alice: Madness Returns* (Steam o EA App) installata su entrambi i PC.
- Windows 10 o 11. Il gioco e la mod sono a 32 bit.
- Microsoft Visual C++ 2015–2022 Redistributable **x86**.
- La stessa versione di AliceFracturedMinds su entrambi i PC.
- Localhost, una rete locale (LAN) affidabile oppure una VPN affidabile, come Radmin VPN.

Il file `dinput8.dll` della mod include già MadnessPatch 3.1.1. Non è necessario installare MadnessPatch separatamente.

## Cartella del gioco

La mod deve essere installata nella cartella che contiene `AliceMadnessReturns.exe`:

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <Cartella EA>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## Installazione

1. Chiudi il gioco.
2. Crea una copia di backup dei tuoi salvataggi e, se presenti, dei tuoi file `dinput8.dll` e `MadnessPatch.ini`. L'archivio sostituirà questi file.
3. Estrai `AliceFracturedMinds-<version>.zip` nella cartella `Binaries\Win32`, mantenendo la struttura delle cartelle. Dovresti ottenere i seguenti file:

```text
AliceMadnessReturns.exe
dinput8.dll
MadnessPatch.ini
AliceCoop\AliceCoopServer.exe
AliceCoop\AliceCoop.ini
AliceCoop\images\...
```

4. Se il gioco si chiude prima ancora che venga visualizzata la finestra, installa Visual C++ Redistributable x86.

## Gioco cooperativo

1. Entrambi i giocatori avviano normalmente il gioco (tramite Steam o EA App).
2. Premi il tasto `M` per aprire il menu:

   - **Host (Ospitante):** seleziona *Host*, lascia l'indirizzo `127.0.0.1` e premi *Save*. Il server di inoltro verrà avviato sul PC dell'ospitante.
   - **Client:** seleziona *Client*, inserisci l'indirizzo LAN/VPN dell'host e lo stesso numero di porta, quindi premi *Save*.

3. Il ruolo selezionato verrà applicato al successivo avvio del gioco. Dopo aver modificato il ruolo, è necessario riavviare il gioco. L'indirizzo e la porta vengono applicati immediatamente.
4. L'host carica un salvataggio ed entra nel gioco. Il client preme `L`, dal menu principale oppure durante il gioco, per unirsi al checkpoint dell'host.

L'host deve consentire le connessioni UDP in entrata sulla porta utilizzata (predefinita `27018`) tramite Windows Firewall.

**Non inoltrare mai questa porta verso Internet.**

In alternativa al menu, puoi utilizzare gli script presenti nella cartella `AliceCoop`:

- `AliceCoop-Host.bat`
- `AliceCoop-Client.bat [server-ip] [port]`
- `AliceCoop-Server.bat`

Su Steam, il gioco potrebbe riavviarsi automaticamente tramite il client Steam e perdere le impostazioni passate tramite uno script. In tal caso, utilizza `AliceCoop.ini` oppure il menu accessibile premendo il tasto `M`.

## Aggiornamento

1. Chiudi il gioco e il server su entrambi i PC.
2. Conserva una copia dei file `AliceCoop\AliceCoop.ini` e `MadnessPatch.ini`.
3. Estrai il nuovo archivio sovrascrivendo i vecchi file e applica nuovamente le tue impostazioni.
4. Consulta il [registro delle modifiche](../CHANGELOG.md) per conoscere le nuove impostazioni.

## Disinstallazione

Elimina i file `dinput8.dll`, `MadnessPatch.ini` e la cartella `AliceCoop` dalla directory `Binaries\Win32`.

I salvataggi creati dal client durante le sessioni cooperative si trovano nella cartella `AliceCoop\client-saves`.

La mod non modifica alcun file originale del gioco.