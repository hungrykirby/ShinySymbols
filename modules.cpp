#include <./Arduino.h>
#include <auto_command_util.h>
#include "modules.h"

/*
 * 自作関数のうち全固定シンボルで共通に使えそうな
 * 関数をこのファイルにまとめています
 * 
 */

// 設定関連

// delayだと自作の何かを差し込めなくなるので関数を作っています。
void myDelay(int delay_ms, unsigned long method_start_ms = -1) {
  if(method_start_ms == -1){
    method_start_ms = millis();
  }
  while(millis() - method_start_ms < delay_ms){
    // やりたいこと
    delay(1);
  }
  return;
}

void recogizeController() {
    myPush(Button::B, 500, 11);
}

// inoファイルで分割するとデフォルト引数が使えない？っぽかったので作った
/* bool myDelayOne(int delay_ms) {
  myDelay(delay_ms);
  return true;
} */

/*
 * スイッチのボタン操作関連
 */

// ボタンを複数回押す
// params:
//  Button
//  int: ボタンを押した後停止する時間（間隔）
//  int: ボタンを押す回数
bool myPush(Button b, int d, int count = 1) {
  for (int i = 0; i < count; i++){
    myPushButton(b, BUTTON_PUSHING_MSEC, d);
  }
  myDelay(BUTTON_PUSHING_MSEC);
  return true;
}

// ボタンを複数回押す（引数3）
// params:
//  Button
//  int: ボタンを押した後停止する時間（間隔）
//  int: ボタンを押す回数
/* bool myPushCount(Button b, int d, int count) {
  for (int i = 0; i < count; i++){
    myPushButton(b, BUTTON_PUSHING_MSEC, d);
  }
  myDelay(BUTTON_PUSHING_MSEC);
  return true;
}*/

// ボタンを押す
// params:
//  Button
//  int: ボタンを押したままにする時間
//  int: ボタンを押した後何も入力しない時間
bool myPushButton(Button button, int holdtime, int delay_time_ms){
  // method_in = true;
  SwitchController().pressButton(button);
  myDelay(holdtime);
  SwitchController().releaseButton(button);
  myDelay(delay_time_ms);
  // method_in = false;
  return true;
}

// ボタンを押す
// params:
//  Hat
//  int: ボタンを押したままにする時間
//  int: ボタンを押した後何も入力しない時間
bool myPushHatButton(Hat button, int holdtime, int delay_time_ms)
{
  // method_in = true;
  SwitchController().pressHatButton(button);
  myDelay(holdtime);
  SwitchController().releaseHatButton();
  myDelay(delay_time_ms);
  // method_in = false;
  return true;
}

// スティックを倒す
bool myTiltJoystick(int lx_per, int ly_per, int rx_per, int ry_per, int tilt_time_msec, int delay_time_ms)
{
  // method_in = true;
  SwitchController().setStickTiltRatio(lx_per, ly_per, rx_per, ry_per);
  myDelay(tilt_time_msec);
  SwitchController().setStickTiltRatio(0, 0, 0, 0);
  myDelay(delay_time_ms);
  // method_in = false;
  return true;
}

// スティックを倒す＋ボタン
/* bool myTiltJoystick(
  int lx_per, int ly_per, int rx_per, int ry_per, Button button
  int tilt_time_msec_before, int tilt_time_msec_after, int delay_time_ms)
{
  // method_in = true;
  SwitchController().setStickTiltRatio(lx_per, ly_per, rx_per, ry_per);
  myDelay(tilt_time_msec_before);
  SwitchController().pressHatButton(button);
  myDelay(BUTTON_PUSHING_MSEC);
  SwitchController().releaseButton(button);
  myDelay(tilt_time_msec_after);
  SwitchController().setStickTiltRatio(0, 0, 0, 0);
  myDelay(delay_time_ms);
  // method_in = false;
  return true;
}*/

/*
 * 移動パート
 */

void openMap(){
    //タウンマップ開く
    myPush(Button::X, 1000);
    myPushHatButton(Hat::LEFT_UP, 1000, BUTTON_PUSHING_MSEC);
    myPush(Button::A, 2500);
    return;
}

// 位置選択後
void sky(){
    myPush(Button::A, 1100);
    // 選択画面対策として下入力2回
    myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
    myPush(Button::A, 1300);
    myPush(Button::B, 400, 5);
    return;
}



/*
 * 時渡り
 */

// 日付変更する（事前にランクマッチ使用した後の時渡り）
void execTimeLeap(){
  // ホーム画面へ
  if(TIME_LEAP_MODE == RANKBATTLE){
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 4000);
    myPushButton(Button::HOME, BUTTON_PUSHING_MSEC, 1500);
    changeTimeAtHome(3);
  }else if(TIME_LEAP_MODE == SUANA){
    runToSuana();

    // 一回一日進めたうえで画面に戻ってこないと固定シンボルが復活しない気がする。
    suanaTimeLeap(1); // 一日進めて画面に戻ってきて再び巣穴から募集して
    suanaTimeLeap(2); // 一日戻る（ワットもゲット！）

    initPosFromSuana();
  }
}

// ホーム画面でどう時渡りするか
void changeTimeAtHome(int mode){ // mode 1 => go 1 day, mode 2 => 1 day ago, mode 3 => both
  // ホームで設定まで行く
  myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
  for(int i = 0; i < 5; i++){
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
  }
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 1500);
  
  // 設定 > 本体 > 日付と時刻
  myPushHatButton(Hat::DOWN, 1600, 100);
  myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 180);
  for(int i = 0; i < 4; i++){
    // Switchライトは4、普通のやつは9くらい？
    myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 110);
  }
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 600);

  // 日付と時刻 > 現在の日付と時刻　にて、1日進めてOK
  myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
  myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
  if(mode == 3){
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::UP, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, 1000, 100);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
    // 1日戻してOK
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
    myPushHatButton(Hat::LEFT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::LEFT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::LEFT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, 1000, 100);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
  }else if(mode == 1){
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::UP, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, 1000, 100);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
  }else if(mode == 2){
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
    myPushHatButton(Hat::RIGHT, 1000, 100);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
  }
    // ホーム画面 > ゲーム画面
  myPushButton(Button::HOME, BUTTON_PUSHING_MSEC, 1000);
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 3000);
}


/* 
 * 巣穴関連
 * 共通パーツではないのだが、これを使わないため放置している
 */

void runToSuana(){
  // myTiltJoystick(0, 0, 20, -100, 230, BUTTON_PUSHING_MSEC);
  myTiltJoystick(25, -100, 0, 0, 2530, BUTTON_PUSHING_MSEC);
}

void initPosFromSuana(){
  myPush(Button::X, 1000);
  myPushHatButton(Hat::LEFT_UP, 1000, BUTTON_PUSHING_MSEC);
  myPush(Button::A, 2500);
  
  //カーソルを飛ぶ場所に合わせる
  myPushHatButton(Hat::RIGHT_DOWN, 180, BUTTON_PUSHING_MSEC);
  
  myDelay(200);
  myPush(Button::A, 1100);
  // 選択画面対策として下入力2回
  myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
  myPushHatButton(Hat::DOWN, BUTTON_PUSHING_MSEC, 100);
  myPush(Button::A, 1300);
  myPush(Button::B, 400, 5);
}

void suanaTimeLeap(int goorback){
  // 以下の二行は一日進めるとき（goorback == 1）には必要ない
  // ワットが手に入らないため
  // だが、ワットが仮にのこっていると面倒なので処理は残した
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
  myPushButton(Button::B, BUTTON_PUSHING_MSEC, 2600);
  // 募集画面に入る
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 1500);
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 4100); // 通信待機中
  myPushButton(Button::HOME, BUTTON_PUSHING_MSEC, 1500);
  changeTimeAtHome(goorback);
  
  myPushButton(Button::B, BUTTON_PUSHING_MSEC, 600); // 募集終了
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 1000);
  myPushButton(Button::A, BUTTON_PUSHING_MSEC, 4600);
}
