# Instalación y actualización

## Requisitos

- Una copia legítima de *Alice: Madness Returns* (Steam o EA App) instalada en ambos PC.
- Windows 10 u 11. El juego y el mod son de 32 bits.
- Microsoft Visual C++ 2015–2022 Redistributable **x86**.
- La misma versión de AliceFracturedMinds en ambos PC.
- Localhost, una red local (LAN) de confianza o una VPN de confianza, como Radmin VPN.

El archivo `dinput8.dll` del mod ya incluye MadnessPatch 3.1.1, por lo que no es necesario instalar MadnessPatch por separado.

## Carpeta del juego

El mod debe instalarse en la carpeta que contiene `AliceMadnessReturns.exe`:

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <Carpeta EA>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## Instalación

1. Cierra el juego.
2. Haz una copia de seguridad de tus partidas guardadas y, si existen, de tus propios archivos `dinput8.dll` y `MadnessPatch.ini`. El archivo comprimido los reemplazará.
3. Extrae `AliceFracturedMinds-<version>.zip` en la carpeta `Binaries\Win32`, manteniendo la estructura de directorios. Deberías obtener los siguientes archivos:

```text
AliceMadnessReturns.exe
dinput8.dll
MadnessPatch.ini
AliceCoop\AliceCoopServer.exe
AliceCoop\AliceCoop.ini
AliceCoop\images\...
```

4. Si el juego se cierra antes de que aparezca su ventana, instala Visual C++ Redistributable x86.

## Juego cooperativo

1. Ambos jugadores inician el juego normalmente (a través de Steam o EA App).
2. Pulsa la tecla `M` para abrir el menú:

   - **Host (Anfitrión):** selecciona *Host*, mantén la dirección `127.0.0.1` y pulsa *Save*. El servidor de retransmisión se iniciará en el PC del anfitrión.
   - **Client (Cliente):** selecciona *Client*, introduce la dirección LAN/VPN del anfitrión y el mismo número de puerto. Después, pulsa *Save*.

3. El rol seleccionado se aplicará la próxima vez que se inicie el juego. Si cambias el rol, tendrás que reiniciar el juego. La dirección y el puerto se aplican inmediatamente.
4. El anfitrión carga una partida guardada y entra en el juego. El cliente pulsa `L`, ya sea en el menú principal o durante la partida, para unirse al punto de control del anfitrión.

El anfitrión debe permitir las conexiones UDP entrantes en el puerto correspondiente (por defecto, `27018`) a través del Firewall de Windows.

**Nunca redirijas este puerto hacia Internet.**

En lugar de utilizar el menú, también puedes usar los scripts de la carpeta `AliceCoop`:

- `AliceCoop-Host.bat`
- `AliceCoop-Client.bat [server-ip] [port]`
- `AliceCoop-Server.bat`

En Steam, el juego puede reiniciarse automáticamente a través del cliente de Steam y perder la configuración proporcionada por un script. En ese caso, utiliza `AliceCoop.ini` o el menú que se abre con la tecla `M`.

## Actualización

1. Cierra el juego y el servidor en ambos PC.
2. Guarda una copia de los archivos `AliceCoop\AliceCoop.ini` y `MadnessPatch.ini`.
3. Extrae el nuevo archivo comprimido sobre los archivos anteriores y vuelve a aplicar tu configuración.
4. Consulta el [registro de cambios](../CHANGELOG.md) para conocer las nuevas opciones de configuración.

## Desinstalación

Elimina los archivos `dinput8.dll`, `MadnessPatch.ini` y la carpeta `AliceCoop` del directorio `Binaries\Win32`.

Las partidas guardadas creadas por el cliente durante las sesiones cooperativas se encuentran en `AliceCoop\client-saves`.

El mod no modifica ningún archivo original del juego.