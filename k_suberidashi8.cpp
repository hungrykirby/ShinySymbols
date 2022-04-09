#include <auto_command_util.h>
#include "modules.h"
#include "k_suberidashi8.h"

/*
 * カンムリ雪原滑り出し雪原 固定シンボル8
 * ユキメノコ
 * https://yakkun.com/swsh/map.htm?place=suberidashi
 * 
 */


KSuberidashi8::KSuberidashi8(int pokemon) {
    this->symbol = pokemon;
}

void KSuberidashi8::moveToInitialPlayerPosition() {
    openMap();

    myPushHatButton(Hat::RIGHT, 100, BUTTON_PUSHING_MSEC);

    myDelay(200);

    sky();
}

void KSuberidashi8::symbolEncount() {
    myTiltJoystick(-2, 100, 0, 0, 1000, 30);
    myTiltJoystick(-27, 100, 0, 0, 1000, BUTTON_PUSHING_MSEC);
    myTiltJoystick(-37, 100, 0, 0, 1500, BUTTON_PUSHING_MSEC);

    // 万が一接触できなかった場合、野生ポケモンが接近してこないところまで移動
    SwitchController().setStickTiltRatio(-60, -100, 0, 0);
    myDelay(5000);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);


    // 戦闘
    myPush(Button::A, 200, 2);
    myPush(Button::B, 200, 5);

    myDelay(this->convertToMSecFromPokemon());
    
    myPush(Button::B, 200, 5);

    // 戦闘開始、色違い光モーションなければ十字上＞逃げる
    // 色違いならば、1つめの上入力間に合わないため戦闘＞自爆技で自分側瀕死
    // Aボタンを2回以上連続して押す場合は、次のポケモン選択画面で一番上以外のポケモンを繰り出さないようにする
    myPushHatButton(Hat::UP, BUTTON_PUSHING_MSEC, 2200);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 800);
    myPush(Button::B, 400, 2);
    myPushHatButton(Hat::UP, 1500, BUTTON_PUSHING_MSEC);
    
    //草むらからポケモンがやってくることがあるため、少し移動
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 500);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 400);
    SwitchController().setStickTiltRatio(-100, -100, 0, 0);
    myDelay(100);
    SwitchController().setStickTiltRatio(20, -100, 0, 0);
    myPush(Button::B, 100, 3);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
}

int KSuberidashi8::convertToMSecFromPokemon() {
    if (this->symbol == FLOSLASS) {
        return 4500;
    }
    return 4500;
}

void KSuberidashi8::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
