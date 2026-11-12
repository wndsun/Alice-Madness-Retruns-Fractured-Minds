# Установка и обновление

## Что нужно

- Лицензионная PC-версия *Alice: Madness Returns* (Steam или EA App) на обоих ПК.
- Windows 10 или 11. Игра и мод 32-битные.
- Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- Одинаковая версия AliceFracturedMinds у обоих игроков.
- Один ПК (localhost), локальная сеть или доверенный VPN, например Radmin VPN.

`dinput8.dll` мода уже содержит MadnessPatch 3.1.1 - отдельно MadnessPatch
ставить не нужно.

## Папка игры

Мод распаковывается в папку, где лежит `AliceMadnessReturns.exe`:

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <папка EA>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## Установка

1. Закройте игру.
2. Сделайте копию сохранений и, если есть, своих `dinput8.dll` и
   `MadnessPatch.ini` - архив их заменит.
3. Распакуйте `AliceFracturedMinds-<версия>.zip` в `Binaries\Win32` с
   сохранением папок. Должно получиться:

   ```text
   AliceMadnessReturns.exe
   dinput8.dll
   MadnessPatch.ini
   AliceCoop\AliceCoopServer.exe
   AliceCoop\AliceCoop.ini
   AliceCoop\images\...
   ```

4. Если игра закрывается до появления окна, установите Visual C++
   Redistributable x86.

## Как играть

1. Оба игрока запускают игру обычным способом (Steam / EA App).
2. Нажмите `M`, откроется меню:
   - **Хост**: выберите *Host*, оставьте `127.0.0.1` и нажмите *Save* - на ПК
     хоста запустится сервер.
   - **Клиент**: выберите *Client*, впишите LAN/VPN-адрес хоста и тот же порт,
     нажмите *Save*.
3. Роль применяется при следующем запуске игры - после смены роли перезапустите
   игру. Адрес и порт применяются сразу.
4. Хост загружает сохранение и входит в игру. Клиент нажимает `L` (в главном
   меню или в игре), чтобы присоединиться к чекпоинту хоста.

Хосту нужно разрешить входящий UDP на порту (по умолчанию `27018`) в брандмауэре
Windows. Не пробрасывайте этот порт в Интернет.

Вместо меню можно использовать скрипты из папки `AliceCoop`:
`AliceCoop-Host.bat`, `AliceCoop-Client.bat [ip-сервера] [порт]` и
`AliceCoop-Server.bat`. Steam может перезапустить игру через свой клиент, и
тогда настройки из скрипта теряются - в этом случае используйте `AliceCoop.ini`
или меню `M`.

## Обновление

1. Закройте игру и сервер на обоих ПК.
2. Сохраните копию своих `AliceCoop\AliceCoop.ini` и `MadnessPatch.ini`.
3. Распакуйте новый архив поверх старых файлов и верните свои настройки.
4. Посмотрите [список изменений](../CHANGELOG.md) - там указаны новые настройки.

## Удаление

Удалите `dinput8.dll`, `MadnessPatch.ini` и папку `AliceCoop` из
`Binaries\Win32`. Сохранения клиента в кооперативе лежат в
`AliceCoop\client-saves`. Оригинальные файлы игры мод не меняет.
