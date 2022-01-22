// カンムリ雪原 巨人の寝床 固定シンボル26
// ブラッキー（曇り）など
// https://yakkun.com/swsh/map.htm?place=nedoko

#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko26.h"

KNedoko26::KNedoko26(int pokemon) {
    this->symbol = pokemon;
}

void KNedoko26::moveToInitialPlayerPosition() {
    openMap();

    myPushHatButton(Hat::UP_RIGHT, 110, BUTTON_PUSHING_MSEC);
    myPushHatButton(Hat::RIGHT, 80, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
}

void KNedoko26::symbolEncount() {
    // おじさんの位置から
    myTiltJoystick(-100, 0, 0, 0, 2500, 30);
    myTiltJoystick(-9, -100, 0, 0, 1300, 30);
    myTiltJoystick(10, -100, 0, 0, 1600, 100);
    // 木の位置まで

    myTiltJoystick(-100, 0, 0, 0, 150, 30);

    SwitchController().setStickTiltRatio(47, -100, 0, 0);
    myDelay(500);

    myPush(Button::LCLICK, BUTTON_PUSHING_MSEC, 15);
    myDelay(2000);

    // エンカウントできなかった場合に遠ざかる
    myPushButton(Button::B, BUTTON_PUSHING_MSEC, 50);
    myDelay(1000);

    SwitchController().setStickTiltRatio(0, 0, 0, 0);
    myDelay(100);

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
}

int KNedoko26::convertToMSecFromPokemon() {
    if (this->symbol == UMBREON) {
        return 4000;
    } else if (this->symbol == NIDORINA) {
        return 4500;
    } else if (this->symbol == ELECTABUZZ) {
        return 5500;
    } else if (this->symbol == HEATMOR) {
        return 4500;
    } else if (this->symbol == CRYOGONAL) {
        return 4500;
    } else if (this->symbol == LEAFEON) {
        return 4000;
    }
    return 4500;
}

void KNedoko26::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
