#include <auto_command_util.h>
#include "modules.h"
#include "k_suberidashi12.h"

/*
 * カンムリ雪原滑り出し雪原 固定シンボル12
 * カビゴン、マンムー
 * https://yakkun.com/swsh/map.htm?place=suberidashi
 * 
 */


KSuberidashi12::KSuberidashi12(int pokemon) {
    this->symbol = pokemon;
}

void KSuberidashi12::moveToInitialPlayerPosition() {
    openMap();

    myPushHatButton(Hat::RIGHT, 100, BUTTON_PUSHING_MSEC);

    myDelay(200);

    sky();
}

void KSuberidashi12::symbolEncount() {
    myTiltJoystick(2, 100, 0, 0, 1500, 30);
    myTiltJoystick(-10, 100, 0, 0, 2500, BUTTON_PUSHING_MSEC);

    // 万が一接触できなかった場合、野生ポケモンが接近してこないところまで移動
    SwitchController().setStickTiltRatio(-40, -100, 0, 0);
    myDelay(3000);
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
    SwitchController().setStickTiltRatio(-40, -100, 0, 0);
    myPush(Button::B, 100, 5);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
}

int KSuberidashi12::convertToMSecFromPokemon() {
    if (this->symbol == MAMOSWINE) {
        return 5000;
    } else if (this->symbol == GLALIE_SUBERIDASHI) {
        return 5500;
    } else if (this->symbol == SNORLAX) {
        return 4500;
    } else if (this->symbol == JYNX) {
        return 5500;
    } else if (this->symbol == CRYOGONAL_SUBERIDASHI) {
        return 5500;
    } else if (this->symbol == WEAVILE) {
        return 4500;
    }
    return 4500;
}

void KSuberidashi12::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}