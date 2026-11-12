# AliceFracturedMinds

Кооператив на двоих для PC-версии *Alice: Madness Returns*.

Форк [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op)
от Docwitson, построенный на [MadnessPatch](https://github.com/Wemino/MadnessPatch).

[English](README.md) · [Установка](docs/INSTALL_RU.md) ·
[Настройки](docs/CONFIGURATION.md) · [Известные проблемы](docs/KNOWN_ISSUES.md) ·
[Изменения](CHANGELOG.md) · [GPL-2.0](LICENSE)

Каждый игрок запускает свою копию игры. Небольшой UDP-сервер
(`AliceCoopServer.exe`) передаёт состояние игроков, анимации и мира, а хост
управляет врагами.

## Что нужно

- Лицензионная PC-версия игры (Steam или EA App) у каждого игрока.
- Windows 10/11 и Microsoft Visual C++ 2015-2022 Redistributable **x86**.
- Одинаковая версия AliceFracturedMinds на обоих ПК.
- Один ПК, локальная сеть или доверенный VPN, например Radmin VPN.

## Быстрый старт

1. Скачайте `AliceFracturedMinds-<версия>.zip` в
   [Releases](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/releases).
2. Распакуйте в `<игра>\Binaries\Win32` (папка с `AliceMadnessReturns.exe`).
3. Запустите игру и нажмите `M`:
   - хост: *Host*, *Save* (запускается сервер);
   - клиент: *Client*, адрес хоста, *Save*.
4. После смены роли перезапустите игру. Хост входит в игру, клиент нажимает `L`,
   чтобы присоединиться.

Подробная инструкция: [docs/INSTALL_RU.md](docs/INSTALL_RU.md).

## Управление

| Клавиша | Где | Действие |
| --- | --- | --- |
| `M` | Везде | Меню кооператива |
| `L` | Клиент / жёлтая подсказка | Присоединиться к хосту или запустить ожидающую катсцену |
| `P` | В игре | Телепорт к другому игроку (безопасный) |
| `O` | Клиент в игре | Принудительный телепорт к хосту |
| `K` | Клиент, главное меню | Скопировать прогресс хоста (перезаписывает профиль клиента) |
| `T` | Меню паузы | Шлейфы движения у второй Алисы |

## Сеть

У сервера нет авторизации и шифрования. Используйте его только на своём ПК, в
локальной сети или доверенном VPN и не пробрасывайте порт в Интернет.

## Лицензия

GPL-2.0 - см. [LICENSE](LICENSE), [NOTICE.md](NOTICE.md) и
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md). Мод не связан с Electronic Arts
и Spicy Horse; файлы игры не включены.
