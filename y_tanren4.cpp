#include <auto_command_util.h>
#include "modules.h"
#include "y_tanren4.h"

// ヨロイの孤島 鍛錬平原 固定シンボル4
// エアームド（砂嵐）、レアコイル（雷雨）など
// https://yakkun.com/swsh/map.htm?place=tanren

YTanren4::YTanren4(int pokemon) {
    this->symbol = pokemon;
}

// 移動パート①
void YTanren4::moveToInitialPlayerPosition(){
    openMap();

    myPushHatButton(Hat::UP_RIGHT, 60, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
}

//　移動パート②～戦闘パート
void YTanren4::symbolEncount(){

    // ワット掘り出しおやじ付近
    
    // 方向転換
    myTiltJoystick(100, 0, 0, 0, 100, 30);
    
    // 少し進む
    myTiltJoystick(0, 100, 0, 0, 500, 30);

    SwitchController().setStickTiltRatio(-15, 100, 0, 0);
    myDelay(100);
    for(int i = 0; i < 10; i++){
        SwitchController().pressButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
        SwitchController().releaseButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
    }
    SwitchController().setStickTiltRatio(50, 50, 0, 0);
    myDelay(100);
    for(int i = 0; i < 3; i++){
        SwitchController().pressButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
        SwitchController().releaseButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
    }
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

    // 画面の角度を変える
    SwitchController().setStickTiltRatio(0, 0, -100, -5);
    myDelay(100);
    for(int i = 0; i < 6; i++){
        SwitchController().pressButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
        SwitchController().releaseButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
    }
    myDelay(100);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

    myPush(Button::LCLICK, 200, 30);

    myDelay(100);

    // エンカウントできなかった際に遠ざかる
    SwitchController().setStickTiltRatio(100, 15, 0, 0);
    myDelay(500);
    SwitchController().pressButton(Button::B);
    myDelay(BUTTON_PUSHING_MSEC);
    SwitchController().releaseButton(Button::B);
    myDelay(2000);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
    myDelay(30);

    // 戦闘
    myPush(Button::A, 200, 2);
    myPush(Button::B, 200, 5);

    myDelay(this->convertToMSecFromPokemon());
    
    myPush(Button::B, 200, 5);

    // 戦闘開始、色違い光モーションなければ十字上＞逃げる
    // 色違いならば、1つめの上入力間に合わないため戦闘＞自爆技で自分側瀕死
    // Aボタンを2回以上連続して押す場合は、次のポケモン選択画面で一番上以外のポケモンを繰り出さないようにする
    myPushHatButton(Hat::UP, BUTTON_PUSHING_MSEC, 1000);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 800);
    myPush(Button::B, 400, 2);
    myPushHatButton(Hat::UP, 1500, BUTTON_PUSHING_MSEC);
    myPush(Button::A, 800, 2);
    myPush(Button::B, 100, 5);

    // 草むらからポケモンがやってくることがあるため、少し移動
    SwitchController().setStickTiltRatio(100, 15, 0, 0);
    myPush(Button::B, 100, 5);
    myDelay(500);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
}

int YTanren4::convertToMSecFromPokemon() {
    if (this->symbol == MAGNETON) {
        return 6000;
    } else if (this->symbol == 0) {
        return 5400;
    }
    return 0;
}

void YTanren4::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
