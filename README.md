# デジコミ用ビーコンタイマー マニュアル

デジコミ(LCR)トランシーバ用、自動送信タイマー

デジコミトランシーバのIDやGPS機能を送出するために定期的にPTTを押すタイマー装置です。
音声信号を送出する機能はありません。

ICOM IC-DRC1、ALINCO DJ-PV1Dでの使用を想定しています。
ICOM仕様のハンディ機であれば、ID-31、ID-51等のD-STARハンディ機でも動作すると思います。

# ファームウェア
## lcr-timer_t13_0_1.ino
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

# ハードウェア
## lcr-timer_0_1.mb3
### 部品表

|部品番号|型番|備考
IC1 | AVR ATtiny13A
