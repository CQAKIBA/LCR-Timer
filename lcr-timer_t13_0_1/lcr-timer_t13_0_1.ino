//デジコミタイマー ファームウェア
//2021/08 Daisuke / cqakiba.tokyo

//ArduinoIDE設定
//ボード MicroCore ATtiny13
//Micros enabled

//動作仕様
//基本時間 15,30,45,60秒 3,5,10,15分 (秒単位は流星反射実験を想定)
//ランダム +-10~59s/OFF
//PTT時間5秒
//スイッチ
// 1,2,3:時間設定 4:ランダム設定

//ランダム設定について
//定期繰り返しだと複数人で使用時に連続で混信してしまうので、ランダムにずらす機能。
//標準のrandom関数はtiny13のROMに入らなかったので、適当にデタラメな値が取れる計算式を使う。

#include <EEPROM.h>

//ピン名定義
#define SW1 4 //3
#define SW2 3 //2
#define L1 2  //7
#define L2 1  //6
#define PTT 0 //5

unsigned int  count_wait, count_send;
byte sw;
unsigned long nexttime=1000;
unsigned int  xrandom;

void setup() {
  //IO初期化
  pinMode(L1,  OUTPUT);
  pinMode(L2,  OUTPUT);
  pinMode(PTT, OUTPUT);
  digitalWrite(PTT, HIGH);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  digitalWrite(SW1, HIGH);
  digitalWrite(SW2, HIGH);

  //シード値更新、乱数初期化
  byte seed = EEPROM.read(0);
  EEPROM.write(0, seed + 1);
  xrandom = seed * 6163 + 8101 % 65521;
  
  //初回待ち時間
  count_wait = 10;
}

void loop() {
  //1秒待ち
  while(millis() < nexttime);
  nexttime = nexttime + 1100; //1000ミリ秒処理待ちだけどなんか10%近く速い個体が多いのでちょっと多め。

  //スイッチマトリクス読み取り
  sw = 0;
  digitalWrite(L1, LOW);
  delayMicroseconds(1);
  if(digitalRead(SW1) == 0) sw = sw | 0b0001;
  if(digitalRead(SW2) == 0) sw = sw | 0b0010;
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  delayMicroseconds(1);
  if(digitalRead(SW1) == 0) sw = sw | 0b0100;
  if(digitalRead(SW2) == 0) sw = sw | 0b1000;
  digitalWrite(L2, HIGH); 
  
  //カウント完了時の処理
  if(count_wait <= 0){
    xrandom = (xrandom * 6163 + 8101) % 65521; //乱数更新
      if(sw == 0b0000) count_wait = 15;
      if(sw == 0b0001) count_wait = 30;
      if(sw == 0b0010) count_wait = 45;
      if(sw == 0b0011) count_wait = 60;
      if(sw == 0b0100) count_wait = 60*3;
      if(sw == 0b0101) count_wait = 60*5;
      if(sw == 0b0110) count_wait = 60*10;
      if(sw == 0b0111) count_wait = 60*15;
      if(sw == 0b1000) count_wait = 15 -  5 + xrandom % 10;
      if(sw == 0b1001) count_wait = 30 - 10 + xrandom % 20;
      if(sw == 0b1010) count_wait = 45 - 10 + xrandom % 20;
      if(sw == 0b1011) count_wait = 60 - 15 + xrandom % 30;
      if(sw == 0b1100) count_wait = 60*3  - 30 + xrandom % 60;
      if(sw == 0b1101) count_wait = 60*5  - 30 + xrandom % 60;
      if(sw == 0b1110) count_wait = 60*10 - 30 + xrandom % 60;
      if(sw == 0b1111) count_wait = 60*15 - 30 + xrandom % 60;
    count_send = 5;   //PTTカウンタセット
  }

  //送信トリガ
  if(count_send){
    count_send--;
    digitalWrite(L2, LOW);
    digitalWrite(PTT, LOW);
  } else {
    digitalWrite(L2, HIGH);
    digitalWrite(PTT, HIGH);
  }
  //カウント
  count_wait--;
  //秒LED点滅
  digitalWrite(L1, LOW);
  delay(100);
  digitalWrite(L1, HIGH);
}
