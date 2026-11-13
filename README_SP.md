# Alice Madness Returns Fractured Minds

<p align="center">
  <img src="docs/media//spl01.png" width="1000" alt="AliceFracturedMinds">
</p>

Cooperativo para dos jugadores en la versión para PC de *Alice: Madness Returns*.

Basado en / bifurcado de [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op) de Docwitson, desarrollado sobre [MadnessPatch](https://github.com/Wemino/MadnessPatch).

### Descarga

**`AliceFracturedMinds-1.0.0.zip`** - Extrae el contenido en `<game>\Binaries\Win32` (la carpeta donde se encuentra `AliceMadnessReturns.exe`). Ambos jugadores necesitan utilizar esta misma versión.

### Inicio rápido

1. Inicia el juego normalmente (Steam / EA App) y pulsa **M**.
2. Anfitrión (Host): selecciona *Host* → *Save* (inicia el servidor de retransmisión).
   Cliente (Client): selecciona *Client*, introduce la dirección LAN/VPN del anfitrión → *Save*.
3. Reinicia el juego después de cambiar el rol. El anfitrión entra en la partida y el cliente pulsa **L** para unirse.

Guía completa: [docs/INSTALL.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/docs/INSTALL.md)

### Novedades respecto a Alice Co-op 0.1.0-alpha.1

- Menú cooperativo dentro del juego (**M**): rol, dirección y puerto del servidor; el anfitrión puede iniciar el servidor desde el menú. No se necesita un lanzador externo.
- Posibilidad de observar al anfitrión durante los capítulos de Londres.
- Persecución del Verdugo sincronizada: golpes, retroceso, risa y final de la persecución.
- Aparición compartida de enemigos después de morir, reiniciar y continuar la partida.
- Numerosas correcciones de cierres inesperados (reaparición, cambios de mapa y eliminación de enemigos).
- Corregidos los enemigos duplicados después de continuar la partida, los problemas de sincronización al saltar cinemáticas, los encuentros con Elite Card Guard y las discrepancias en los puntos de control al continuar desde el menú principal.
- Nuevas opciones en `AliceCoop.ini`: `GameConsole`, `Logs`, `Dumps`.

Lista completa: [CHANGELOG.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/CHANGELOG.md)

### Requisitos

- Una copia legítima del juego para PC para cada jugador (Steam o EA App). No se incluyen archivos del juego.
- Windows 10/11, Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- El mismo PC, una red LAN o una VPN de confianza (por ejemplo, Radmin VPN).

> [!WARNING]
> El servidor de retransmisión no dispone de autenticación ni cifrado. Nunca expongas su puerto (UDP 27018) a Internet.
>
> El archivo reemplaza `dinput8.dll` y `MadnessPatch.ini`. Haz copias de seguridad de estos archivos y también de tus partidas guardadas.

### Cómo informar de errores

Los registros (logs) están desactivados por defecto. Establece `Logs = 1` en la sección `[Debug]` de `AliceCoop\AliceCoop.ini`, reproduce el problema y adjunta los archivos de `AliceCoop\logs` al [informe de error](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/issues).