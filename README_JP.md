# Alice Madness Returns Fractured Minds

<p align="center">
  <img src="docs/media//spl01.png" width="1000" alt="AliceFracturedMinds">
</p>

PC版 *Alice: Madness Returns* 用の2人協力プレイMODです。

Docwitsonによって開発された [Alice Co-op](https://github.com/docwitson/Alice-Madness-Returns-Co-op) をベースにしたフォークであり、[MadnessPatch](https://github.com/Wemino/MadnessPatch) を基盤として開発されています。

### ダウンロード

**`AliceFracturedMinds-1.0.0.zip`** — アーカイブを `<game>\Binaries\Win32`（`AliceMadnessReturns.exe` があるフォルダ）に展開してください。両プレイヤーが同じバージョンを使用する必要があります。

### クイックスタート

1. 通常どおりゲームを起動し（Steam / EA App）、**M** キーを押します。
2. ホスト（Host）：*Host* → *Save* を選択します（中継サーバーが起動します）。
   クライアント（Client）：*Client* を選択し、ホストのLAN/VPNアドレスを入力して *Save* を選択します。
3. 役割を変更した後、ゲームを再起動してください。ホストはゲームを開始し、クライアントは **L** キーを押して参加します。

詳細なガイド：[docs/INSTALL.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/docs/INSTALL.md)

### Alice Co-op 0.1.0-alpha.1 からの主な変更点

- ゲーム内協力プレイメニュー（**M**）：役割、サーバーアドレス、ポートを設定できます。ホストはメニューからサーバーを起動できます。外部ランチャーは不要です。
- ロンドンのチャプターでホストのプレイを観戦できるようになりました。
- 処刑人の追跡イベントを同期：攻撃のヒット、ノックバック、笑い声、追跡イベントの終了。
- 死亡、再起動、ゲームの続行後における敵の出現を共有・同期。
- クラッシュに関する多数の修正（リスポーン、マップ変更、敵の終了処理）。
- ゲーム続行後に敵が複製される問題、カットシーンのスキップによる同期ずれ、Elite Card Guard との遭遇時の問題、メインメニューから続行した際のチェックポイントの不一致を修正。
- `AliceCoop.ini` に新しい設定項目を追加：`GameConsole`、`Logs`、`Dumps`。

変更履歴の全一覧：[CHANGELOG.md](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/blob/main/CHANGELOG.md)

### 必要環境

- 各プレイヤーが正規のPC版ゲームを所有していること（Steam または EA App）。ゲーム本体のファイルは含まれていません。
- Windows 10/11、Microsoft Visual C++ 2015-2022 Redistributable **x86**。
- 同じPC、LAN、または信頼できるVPN（例：Radmin VPN）。

> [!WARNING]
> 中継サーバーには認証機能および暗号化機能がありません。サーバーのポート（UDP 27018）をインターネットに公開しないでください。
>
> このアーカイブは `dinput8.dll` と `MadnessPatch.ini` を置き換えます。これらのファイルとゲームのセーブデータは、事前にバックアップしてください。

### バグ報告

ログ機能はデフォルトで無効になっています。`AliceCoop\AliceCoop.ini` の `[Debug]` セクションで `Logs = 1` に設定し、問題を再現してください。その後、`AliceCoop\logs` フォルダ内のファイルを添付して、[Issue](https://github.com/wndsun/Alice-Madness-Retruns-Fractured-Minds/issues) を作成してください。