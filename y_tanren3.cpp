#include <auto_command_util.h>
#include "modules.h"
#include "y_tanren3.h"

// ヨロイの孤島 鍛錬平原 固定シンボル3
// https://yakkun.com/swsh/map.htm?place=tanren

YTanren3::YTanren3(int pokemon) {
    this->symbol = pokemon;
}

// 移動パート①
void YTanren3::moveToInitialPlayerPosition(){
    openMap();

    myPushHatButton(Hat::UP_RIGHT, 60, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
}

//　移動パート②～戦闘パート
void YTanren3::symbolEncount(){

     // ワット掘り出しおやじ付近
    myTiltJoystick(-100, 0, 0, 0, 100, 30);

    SwitchController().setStickTiltRatio(-4, 100, 0, 0);
    myDelay(100);
    for(int i = 0; i < 10; i++){
        SwitchController().pressButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
        SwitchController().releaseButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
    }
    myDelay(100);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

    myDelay(100);

    // エンカウントできなかった際に遠ざかる
    SwitchController().setStickTiltRatio(100, -15, 0, 0);
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

int YTanren3::convertToMSecFromPokemon() {
    if (this->symbol == COMFEY) {
        return 6000;
    } else if (this->symbol == CRUSTLE) {
        return 6000;
    } else if (this->symbol == SCYTHER) {
        return 6000;
    } else if (this->symbol == PELIPPER) {
        return 6000;
    } else if (this->symbol == LUXIO) {
        return 7000;
    } else if (this->symbol == KANGASKHAN) {
        return 5500;
    } else if (this->symbol == DRAPION) {
        return 5500;
    }
    return 0;
}

void YTanren3::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
