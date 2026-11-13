# インストールとアップデート

## 必要条件

- 両方のPCに正規版の *Alice: Madness Returns*（Steam または EA App）がインストールされていること。
- Windows 10 または 11。ゲームとMODは32ビット版です。
- Microsoft Visual C++ 2015–2022 Redistributable **x86**。
- 両方のPCで同じバージョンの AliceFracturedMinds を使用すること。
- Localhost、信頼できるローカルネットワーク（LAN）、または Radmin VPN などの信頼できる VPN 接続。

MODの `dinput8.dll` には MadnessPatch 3.1.1 がすでに含まれています。MadnessPatch を別途インストールする必要はありません。

## ゲームフォルダ

MODは `AliceMadnessReturns.exe` があるフォルダにインストールしてください。

```text
Steam:  <SteamLibrary>\steamapps\common\Alice Madness Returns\Binaries\Win32
EA App: <EAフォルダ>\Alice Madness Returns\Game\Alice2\Binaries\Win32
```

## インストール方法

1. ゲームを終了します。
2. セーブデータ、および自分で使用している `dinput8.dll` と `MadnessPatch.ini` がある場合は、それらのバックアップを作成してください。アーカイブ内のファイルによって置き換えられます。
3. `AliceFracturedMinds-<version>.zip` をフォルダ構造を維持したまま `Binaries\Win32` に展開します。次のようなファイル構成になります。

```text
AliceMadnessReturns.exe
dinput8.dll
MadnessPatch.ini
AliceCoop\AliceCoopServer.exe
AliceCoop\AliceCoop.ini
AliceCoop\images\...
```

4. ゲームウィンドウが表示される前にゲームが終了してしまう場合は、Visual C++ Redistributable x86 をインストールしてください。

## マルチプレイ

1. 両方のプレイヤーが通常どおり Steam または EA App からゲームを起動します。
2. `M` キーを押してメニューを開きます。

   - **Host（ホスト）：** *Host* を選択し、アドレス `127.0.0.1` はそのままにして *Save* を押します。中継サーバーがホスト側のPCで起動します。
   - **Client（クライアント）：** *Client* を選択し、ホストの LAN/VPN アドレスと同じポート番号を入力して、*Save* を押します。

3. 選択した役割は次回のゲーム起動時に適用されます。役割を変更した場合は、ゲームを再起動してください。アドレスとポート番号はすぐに適用されます。
4. ホストはセーブデータをロードしてゲームプレイを開始します。クライアントはメインメニューまたはゲームプレイ中に `L` キーを押すことで、ホストのチェックポイントに参加できます。

ホスト側では、Windows ファイアウォールで指定されたポート（デフォルトは `27018`）の UDP 着信接続を許可する必要があります。

**このポートをインターネットに公開するためのポートフォワーディングは絶対に行わないでください。**

メニューの代わりに `AliceCoop` フォルダ内のスクリプトを使用することもできます。

- `AliceCoop-Host.bat`
- `AliceCoop-Client.bat [server-ip] [port]`
- `AliceCoop-Server.bat`

Steam 版では、ゲームが Steam クライアント経由で自動的に再起動し、スクリプトから渡された設定が失われる場合があります。その場合は `AliceCoop.ini` または `M` キーで開くメニューを使用してください。

## アップデート

1. 両方のPCでゲームとサーバーを終了します。
2. `AliceCoop\AliceCoop.ini` と `MadnessPatch.ini` のコピーを保存します。
3. 新しいアーカイブを古いファイルに上書きする形で展開し、設定を再適用してください。
4. 新しい設定については [変更履歴](../CHANGELOG.md) を確認してください。

## アンインストール

`Binaries\Win32` フォルダから `dinput8.dll`、`MadnessPatch.ini`、および `AliceCoop` フォルダを削除してください。

協力プレイ中にクライアント側で作成されたセーブデータは `AliceCoop\client-saves` に保存されています。

このMODはゲームのオリジナルファイルを一切変更しません。