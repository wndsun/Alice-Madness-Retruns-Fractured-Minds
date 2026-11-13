# Alice Madness Returns Fractured Minds

<p align="center">
  <img src="docs/media//spl01.png" width="1000" alt="AliceFracturedMinds">
</p>

Modalità cooperativa per due giocatori nella versione PC di *Alice: Madness Returns*.

Basata su / derivata come fork da [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op) di Docwitson, sviluppata sulla base di [MadnessPatch](https://github.com/Wemino/MadnessPatch).

### Download

**`AliceFracturedMinds-1.0.0.zip`** — Estrai l'archivio nella cartella `<game>\Binaries\Win32` (la cartella che contiene `AliceMadnessReturns.exe`). Entrambi i giocatori devono utilizzare la stessa versione.

### Avvio rapido

1. Avvia il gioco normalmente (tramite Steam / EA App) e premi **M**.
2. Host: seleziona *Host* → *Save* (verrà avviato il server di inoltro).
   Client: seleziona *Client*, inserisci l'indirizzo LAN/VPN dell'host → *Save*.
3. Riavvia il gioco dopo aver cambiato ruolo. L'host entra nella partita, mentre il client preme **L** per unirsi.

Guida completa: [docs/INSTALL.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/docs/INSTALL.md)

### Novità rispetto ad Alice Co-op 0.1.0-alpha.1

- Menu cooperativo direttamente nel gioco (**M**): ruolo, indirizzo e porta del server; l'host può avviare il server dal menu. Non è necessario alcun launcher esterno.
- Possibilità di osservare l'host durante i capitoli di Londra.
- Inseguimento del Boia sincronizzato: colpi, respinta, risata e conclusione dell'inseguimento.
- Generazione condivisa dei nemici dopo la morte, il riavvio e la continuazione della partita.
- Numerose correzioni dei crash (respawn, cambi di mappa e rimozione dei nemici).
- Risolti i problemi dei nemici duplicati dopo aver continuato la partita, la desincronizzazione durante il salto delle scene cinematiche, gli incontri con gli Elite Card Guard e le discrepanze dei checkpoint quando si continua dal menu principale.
- Nuove opzioni in `AliceCoop.ini`: `GameConsole`, `Logs`, `Dumps`.

Elenco completo delle modifiche: [CHANGELOG.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/CHANGELOG.md)

### Requisiti

- Una copia legittima del gioco per PC per ciascun giocatore (Steam o EA App). I file del gioco non sono inclusi.
- Windows 10/11, Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- Lo stesso PC, una rete LAN oppure una VPN affidabile (ad esempio Radmin VPN).

> [!WARNING]
> Il server di inoltro non dispone di autenticazione né di crittografia. Non esporre mai la sua porta (UDP 27018) a Internet.
>
> L'archivio sostituisce `dinput8.dll` e `MadnessPatch.ini`. Effettua copie di backup di questi file e dei tuoi salvataggi di gioco.

### Segnalazione dei bug

I log sono disattivati per impostazione predefinita. Imposta `Logs = 1` nella sezione `[Debug]` di `AliceCoop\AliceCoop.ini`, riproduci il problema e allega i file presenti in `AliceCoop\logs` a una [segnalazione](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/issues).