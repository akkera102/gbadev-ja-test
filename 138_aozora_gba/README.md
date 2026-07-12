# 果てしなく青い、この空の下で…。 for GBA

## ご案内

このソフトはWindows版「果てしなく青い、この空の下で…。」をGBAへ移植したものです。ゲームデータは付属していない為、製品を持っている方のみ遊べます。

![README](README.png)

## 前準備

対応バージョンと必要ファイルは以下のとおりです。
```
・初回版（通常版）
・メモリアル版
・DLsite

※ 未対応：完全版、TECH GIAN BRILLIANT 2013年 上半期
```
```
・DLsite
  「AOZORA」フォルダ全体を「gbfs\data」にコピーしてください。

・初回版（通常版）
・メモリアル版
  DLsiteと同様に「AOZORA」フォルダ全体を「gbfs\data」にコピーします。
  AOZORAフォルダ内に「track」フォルダを作り、CDDAをリッピングして「track_02.wav」を配置します。
```
作業が完了すると、以下の構成になります。
```
data/
  └ AOZORA/
       ├ BGM/
       ├ SE/
       └ track/
```

## インストール環境

以下の条件で「make.bat」を実行します。

- Windows 11 x64
- Python3とPillowのインストールされており、コマンドプロンプトでパスが通っていることを確認してください。
- Microsoft Visual C++ Redistributable(Visual Studio 2015, 2017, 2019, and 2022) 64bit版のインストール

変換時間はi5+SSD環境で15分ほど。約30.5MBのROMが作られれば成功です。ちなみにコンバート中にエラーが発生しても止まりません。やり直したい場合はDOSプロンプト画面を閉じてください。

## お約束

- 「果てしなく青い、この空の下で…。」はTOPCATの著作物です
- このソフトに関する問い合わせをTOPCATにしないでください
- このソフトを使用して発生した問題など、当方は一切責任を負いません
- 利用は個人で使用する範囲に留めてください

## （どろり濃厚）言い訳タイム

音質はこの辺りが限界でした。お察しください。orz

- 800x600画像を798x532にクリッピング。それぞれ3.325で割って240x160にしています
- 追加シナリオは最初から解放されています。青色しおりにならない仕様です
- 攻略情報を入れました。ゲーム開始時に選択してください
- 既読機能はスタートボタンで高速スキップ、セレクトボタンで画面スキップします
- 全ハッピークリア後はバッドルートに入っても、全ハッピーEDになります。ご了承ください
- 攻略は「雨音→悠夏→藍→明日菜→文乃」の順番がオススメです
- 全ルートのプレイ時間は20-25時間程度です
- セーブの種類はSRAMのみ対応しています
- 感想やバグなどありましたら[ご一報](https://akkera102.hatenablog.com/)ください

## クリアフラグ

クリアフラグはセーブデータのアドレス0x10～0x14に格納されています。
```
アドレス
  0x10 雨音
  0x11 悠夏
  0x12 藍
  0x13 明日菜
  0x14 文乃

内容
  0x03 ハッピーとバッド両方
  0x02 ハッピー
  0x01 バッド
```
オールクリアにしたい場合、0x10～0x14を0x03で埋めてください。

## 謝辞

コンバータ関連のプログラムは下記のツールを参考にさせて頂きました。先人の素晴らしい解析作業に深く感謝いたします。

- Garbro(morkt)
- TopCatScriptSimpleTool(julixian)
- ifspd7(yui)
- TCS2WAV(aozora DNML)

## ライセンス

- 私の書いたGBAソースコード（CC0）
- コンバータ関連のpythonコード、Cコード（GPL2 or later）
- CULT-GBA and fixed Lorenzooone ver(MIT)
- ulc-codec(Unlicense)
- gbfs(MIT)
- libgba(LGPL2.0 dynamic link)
- crt0.s(MPL2.0)

## 動作環境

- mGBA 0.10.5
- GBA.emu(Android) Mar 17 2026
- EverDrive GBA X5
- EZ-FLASH DE

## 開発環境

- Windows11 Pro 64bit
- devkitPro(gcc v15.1.0 devkitARM r66)
- VisualBoyAdvance 1.8.0-beta 3
- Python3.13.7 + pillow11.3.0
- MSYS2(gcc version 15.2.0)

## 簡単な履歴

2026/07/13 v0.01

- 完成しました

2026/07/07 beta

- 色々修正

2026/07/03 beta

- おためし公開
