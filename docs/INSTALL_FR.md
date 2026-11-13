# Installation et mise à jour

## Configuration requise

- Une copie légitime de *Alice: Madness Returns* (Steam ou EA App) installée sur les deux PC.
- Windows 10 ou 11. Le jeu et le mod sont en 32 bits.
- Microsoft Visual C++ 2015–2022 Redistributable **x86**.
- La même version d'AliceFracturedMinds sur les deux PC.
- Localhost, un réseau local (LAN) de confiance ou un VPN de confiance, tel que Radmin VPN.

Le fichier `dinput8.dll` du mod contient déjà MadnessPatch 3.1.1. Il n'est donc pas nécessaire d'installer MadnessPatch séparément.

## Dossier du jeu

Le mod doit être installé dans le dossier contenant `AliceMadnessReturns.exe` :

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <Dossier EA>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## Installation

1. Fermez le jeu.
2. Sauvegardez vos fichiers de sauvegarde ainsi que vos propres fichiers `dinput8.dll` et `MadnessPatch.ini`, s'ils sont présents. L'archive remplacera ces fichiers.
3. Extrayez `AliceFracturedMinds-<version>.zip` dans le dossier `Binaries\Win32`, en conservant la structure des dossiers. Vous devriez obtenir les fichiers suivants :

```text
AliceMadnessReturns.exe
dinput8.dll
MadnessPatch.ini
AliceCoop\AliceCoopServer.exe
AliceCoop\AliceCoop.ini
AliceCoop\images\...
```

4. Si le jeu se ferme avant même que sa fenêtre n'apparaisse, installez Visual C++ Redistributable x86.

## Jeu en coopération

1. Les deux joueurs lancent le jeu normalement (via Steam ou EA App).
2. Appuyez sur la touche `M` pour ouvrir le menu :

   - **Host (Hôte) :** sélectionnez *Host*, conservez l'adresse `127.0.0.1`, puis appuyez sur *Save*. Le serveur relais démarrera sur le PC de l'hôte.
   - **Client :** sélectionnez *Client*, saisissez l'adresse LAN/VPN de l'hôte ainsi que le même numéro de port, puis appuyez sur *Save*.

3. Le rôle sélectionné sera appliqué au prochain lancement du jeu. Si vous le modifiez, vous devrez redémarrer le jeu. L'adresse et le port sont appliqués immédiatement.
4. L'hôte charge une sauvegarde et entre dans le jeu. Le client appuie sur `L`, depuis le menu principal ou pendant une partie, pour rejoindre le point de contrôle de l'hôte.

L'hôte doit autoriser les connexions UDP entrantes sur le port utilisé (par défaut `27018`) dans le pare-feu Windows.

**Ne redirigez jamais ce port vers Internet.**

Vous pouvez également utiliser les scripts présents dans le dossier `AliceCoop` à la place du menu :

- `AliceCoop-Host.bat`
- `AliceCoop-Client.bat [server-ip] [port]`
- `AliceCoop-Server.bat`

Sur Steam, le jeu peut redémarrer automatiquement via le client Steam et perdre les paramètres transmis par un script. Dans ce cas, utilisez `AliceCoop.ini` ou le menu accessible avec la touche `M`.

## Mise à jour

1. Fermez le jeu et le serveur sur les deux PC.
2. Conservez une copie de vos fichiers `AliceCoop\AliceCoop.ini` et `MadnessPatch.ini`.
3. Extrayez la nouvelle archive par-dessus les anciens fichiers, puis réappliquez vos paramètres.
4. Consultez le [journal des modifications](../CHANGELOG.md) pour découvrir les nouveaux paramètres.

## Désinstallation

Supprimez les fichiers `dinput8.dll`, `MadnessPatch.ini` ainsi que le dossier `AliceCoop` du répertoire `Binaries\Win32`.

Les sauvegardes créées par le client pendant les parties en coopération se trouvent dans `AliceCoop\client-saves`.

Le mod ne modifie aucun fichier original du jeu.