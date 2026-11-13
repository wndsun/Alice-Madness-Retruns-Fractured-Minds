# Alice Madness Returns Fractured Minds

<p align="center">
  <img src="docs/media//spl01.png" width="1000" alt="AliceFracturedMinds">
</p>

Mode coopératif à deux joueurs pour la version PC de *Alice: Madness Returns*.

Basé sur / dérivé du projet [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op) créé par Docwitson, et développé sur la base de [MadnessPatch](https://github.com/Wemino/MadnessPatch).

### Téléchargement

**`AliceFracturedMinds-1.0.0.zip`** — Extrayez l'archive dans le dossier `<game>\Binaries\Win32` (le dossier contenant `AliceMadnessReturns.exe`). Les deux joueurs doivent utiliser la même version.

### Démarrage rapide

1. Lancez le jeu normalement (via Steam / EA App), puis appuyez sur **M**.
2. Hôte (Host) : sélectionnez *Host* → *Save* (cela démarre le serveur relais).
   Client (Client) : sélectionnez *Client*, saisissez l'adresse LAN/VPN de l'hôte, puis sélectionnez *Save*.
3. Redémarrez le jeu après avoir changé de rôle. L'hôte entre dans la partie et le client appuie sur **L** pour rejoindre la session.

Guide complet : [docs/INSTALL.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/docs/INSTALL.md)

### Nouveautés par rapport à Alice Co-op 0.1.0-alpha.1

- Menu coopératif intégré au jeu (**M**) : choix du rôle, adresse et port du serveur. L'hôte peut démarrer le serveur directement depuis le menu. Aucun lanceur externe n'est nécessaire.
- Possibilité d'observer l'hôte pendant les chapitres de Londres.
- Synchronisation de la poursuite du Bourreau : coups, projection, rire et fin de la poursuite.
- Apparition partagée des ennemis après la mort, le redémarrage et la reprise de la partie.
- Nombreuses corrections des plantages (réapparition, changements de carte et suppression des ennemis).
- Correction des ennemis dupliqués après la reprise de la partie, des problèmes de désynchronisation lors du passage des cinématiques, des rencontres avec les Elite Card Guard et des incohérences des points de contrôle lors de la reprise depuis le menu principal.
- Nouvelles options dans `AliceCoop.ini` : `GameConsole`, `Logs`, `Dumps`.

Liste complète des modifications : [CHANGELOG.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/CHANGELOG.md)

### Configuration requise

- Une copie légitime du jeu sur PC pour chaque joueur (Steam ou EA App). Les fichiers du jeu ne sont pas inclus.
- Windows 10/11, Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- Le même PC, un réseau local (LAN) ou un VPN fiable (par exemple, Radmin VPN).

> [!WARNING]
> Le serveur relais ne dispose d'aucun système d'authentification ni de chiffrement. N'exposez jamais son port (UDP 27018) sur Internet.
>
> L'archive remplace `dinput8.dll` et `MadnessPatch.ini`. Effectuez des copies de sauvegarde de ces fichiers ainsi que de vos sauvegardes de jeu.

### Signaler des bugs

Les journaux (logs) sont désactivés par défaut. Définissez `Logs = 1` dans la section `[Debug]` de `AliceCoop\AliceCoop.ini`, reproduisez le problème et joignez les fichiers du dossier `AliceCoop\logs` à un [rapport de bug](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/issues).