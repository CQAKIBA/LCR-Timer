# デジコミ用ビーコンタイマー マニュアル

デジコミ(LCR)トランシーバ用、自動送信タイマー

デジコミトランシーバのIDやGPS機能を送出するために定期的にPTTを押すタイマー装置です。

音声信号を送出する機能はありません。

ICOM IC-DRC1、ALINCO DJ-PV1Dでの使用を想定しています。

ICOM仕様のハンディ機であれば、ID-31、ID-51等のD-STARハンディ機でも動作すると思います。

# ライセンス
CC BY-SA

クリエイティブコモンズ 表示-継承

# ファームウェア
## lcr-timer_t13_0_1.ino

### 動作
- 送信間隔は設定スイッチで変更可能。
- 運悪く他局とタイミングが一致する事を防ぐための送信間隔ランダム化機能。
- 送信時間は5秒固定。
- 秒間隔での送信は流星反射実験を想定。

### 設定スイッチ一覧
|1(時間)|2(時間)|3(時間)|4(ランダム)|動作|
|----|----|----|----|----|
|OFF|OFF|OFF|OFF|15秒|
|ON |OFF|OFF|OFF|30秒|
|OFF|ON |OFF|OFF|45秒|
|ON |ON |OFF|OFF|60秒|
|OFF|OFF|ON |OFF|3分|
|ON |OFF|ON |OFF|5分|
|OFF|ON |ON |OFF|10分|
|ON |ON |ON |OFF|15分|
|OFF|OFF|OFF|ON|15秒 ±5秒|
|ON |OFF|OFF|ON|30秒 ±10秒|
|OFF|ON |OFF|ON|45秒 ±10秒|
|ON |ON |OFF|ON|60秒 ±15秒|
|OFF|OFF|ON |ON|3分 ±30秒|
|ON |OFF|ON |ON|5分 ±30秒|
|OFF|ON |ON |ON|10分 ±30秒|
|ON |ON |ON |ON|15分 ±30秒|

![image](https://user-images.githubusercontent.com/10165993/138369955-022a5684-0e25-4cf7-ab3d-da6e52c73ab4.png)

# ハードウェア
## lcr-timer_0_1.mb3
- CPUの内部発振器で動作させているため、時間精度は非常に低いです。

![image](https://github.com/CQAKIBA/LCR-Timer/blob/main/drc-decoy_0_1.png)

### 部品表

|部品番号|型番|備考|
|----|----|----|
|IC1 |ATtiny13A|AVRマイコン|
|SW1|EDS104SZ|4回路DIPスイッチ|
|R1～2|1kΩ|
|R3|33kΩ|マイクPTT回路用|
|C1|0.1uF||
|D1～5|1N4148|小信号ダイオード|
|LED1|OSG5DA3133A|緑色LED|
|LED2|OSDR3133A|赤色LED|
|ケーブル|25SS-10, 425-25S|ICOMマイク端子が狭くて厄介なので適宜|
