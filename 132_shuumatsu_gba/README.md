# 終末の過ごし方 for GBA（作業中、WIP）

## ご案内

このソフトはWindows版「終末の過ごし方」をGBAへ移植したものです。ゲームデータは付属していない為、製品を持っている方のみ遊べます。

![README](README.png)

## 前準備

対応バージョンと必要ファイルは以下のとおりです。「gbfs\data」フォルダに入れてください。一部のadpファイルは重複して別フォルダにも存在します。同じサイズ、データですのでどちらを使用してもかまいません。
```
・DVD版
・TECH GIAN（2015/1)
・DLSite（ファイル容量　510.55MBと記載。将来変更の可能性あり）

※ 未対応：CD版、DVD-PG版
```
```
DOM.adp

GRAPHIC.DSK
GRAPHIC.PFT

ido.adp
od_m.adp
OD_MO.adp
od_p.adp
OD_WC.adp
OD_WO.adp
paper.adp
paperbag.adp
radio.adp
radionz.adp

scene.DSK
scene.PFT

sd_m.adp
sd_p.adp
TIMEBELL.adp

WIPE.DSK
WIPE.PFT

----
計20ファイル
```

## インストール環境

以下の条件で「make.bat」を実行します。

- windows 10 x64（もしくは11）
- Python3とPillowのインストール。プロンプトのパスが通っていることを確認してください
- Microsoft Visual C++ Redistributable(Visual Studio 2015, 2017, 2019, and 2022) 64bit版のインストール

変換時間はi5+SSD環境で10分ほど。約23MBのROMが作られれば成功です。ちなみにコンバート中にエラーが発生しても止まりません。やり直したい場合はDOSプロンプト画面を閉じてください。

## お約束

- 「終末の過ごし方」はAbogado Powersの著作物です
- このソフトに関する問い合わせをAbogado Powersにしないでください
- このソフトを使用して発生した問題など、当方は一切責任を負いません
- 利用は個人で使用する範囲に留めてください

## 謝辞

## 言い訳タイム（良い終末を）

無謀にもアルファブレンドエフェクトを使っているため、一部でお見苦しい点もあるかと思います。

- 640x480サイズを4ドット削って636x480。3で割って212x160表示にしました
- オートセーブ機能はない為、エンディング後に電源を切ると既読フラグが消えます。「最初から」を選んでセーブしてください
- オプションの「画像、音楽、効果音」は内部変数を書き換えています。不具合で停止することはありませんが場面変化するまでそのままです
- スタートボタンもしくはセレクトボタンで既読スキップ可能です
- 全ルートのプレイ時間は3時間程度になります
- セーブの種類はSRAMです。FLASHはCUBIC STYLE製のみ対応しています
- バージョンアップした場合、セーブデータに互換性はなくなります。ご了承ください
- 感想やバグなどありましたら[ご一報](https://akkera102.hatenablog.com/)願います

## ライセンス

- 私の書いたGBAソースコード（CC0）
- コンバータ関連のpythonコード、Cコード（GPL2 or later）
- Visual Novels resource browser GARbro(MIT)
- CULT-GBA and fixed Lorenzooone ver(MIT)
- libgba(LGPL2.0 dynamic link)
- gbfs(MIT)
- crt0.s(MPL2.0)

## 動作環境

- mGBA 0.10.5
- GBA.emu(Android) Apr 30 2024
- EverDrive X5
- EZ-FLASH DE

## 開発環境

- windows10 pro 64bit
- devkitPro(gcc v15.1.0 devkitARM r66)
- VisualBoyAdvance 1.8.0-beta 3
- Python3.13.1 + pillow11.0.0
- MSYS2(gcc version 13.2.0)

## 簡単な履歴

2025/08/01 beta

- おためし公開（音楽なし）

