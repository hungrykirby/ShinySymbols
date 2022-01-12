// カンムリ雪原 巨人の寝床 固定シンボル23
// ニンフィア（霧）など
// https://yakkun.com/swsh/map.htm?place=nedoko

// 11/14 ブラッキー <- 違う

#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko23.h"

KNedoko23::KNedoko23(int pokemon){
    this->symbol = pokemon;
}

// 移動パート①
void KNedoko23::moveToInitialPlayerPosition(){
    openMap();

    myPushHatButton(Hat::UP_RIGHT, 110, BUTTON_PUSHING_MSEC);
    myPushHatButton(Hat::RIGHT, 80, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
    return;
}

//　移動パート②～戦闘パート
void KNedoko23::symbolEncount(){

    // おじさんの位置から
    myTiltJoystick(-100, 0, 0, 0, 2500, 30);
    myTiltJoystick(-9, -100, 0, 0, 1300, 30);
    myTiltJoystick(10, -100, 0, 0, 1600, 100);
    // 木の位置まで

    myTiltJoystick(-100, 0, 0, 0, 100, 30);

    // myTiltJoystick(-10, -100, 0, 0, 3700, 30);
    SwitchController().setStickTiltRatio(-10, -100, 0, 0);
    myDelay(500);
    SwitchController().pressButton(Button::B);
    myDelay(BUTTON_PUSHING_MSEC);
    SwitchController().releaseButton(Button::B);
    myDelay(1800);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
    myDelay(100);

    // このへん天気や時間でけっこう変わりそう
    // ここで岩にこするくらい
    myTiltJoystick(-62, -100, 0, 0, 1000, 100);
    myTiltJoystick(-100, -100, 0, 0, 100, 100);
    // myTiltJoystick(0, -100, 0, 0, 1000, 30);
    // myTiltJoystick(-25, -100, 0, 0, 1600, 30); -> シャンデラ

    myTiltJoystick(-80, -100, 0, 0, 2500, 30);
    myTiltJoystick(90, -100, 0, 0, 2000, 30);
    // myTiltJoystick(0, -100, 0, 0, 3000, 30);

    SwitchController().setStickTiltRatio(-6, -100, 0, 0);
    myDelay(100);
    for(int i = 0; i < 9; i++){
        SwitchController().pressButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
        SwitchController().releaseButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
    }
    myDelay(200);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

    myDelay(100);

    // myTiltJoystick(-100, -100, 0, 0, 1000, 30);
    // エンカウントできなかった際に遠ざかる
    SwitchController().setStickTiltRatio(-100, -50, 0, 0);
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
    return;
}

int KNedoko23::convertToMSecFromPokemon() {
    if (this->symbol == ARAQUANID) {
        // 1/4 雨 オニシズクモ ＋ かがくへんかガス
        return 6000;
    } else if (this->symbol == SYLVEON) {
        // 11-10 霧 (ミストフィールド) ニンフィア ＋ かがくへんかガス
        return 6000;
    } else if (this->symbol == NIDOKING_NEDOKO23) {
        // 1/5 雪 ニドキング + かがくへんかガス
        return 5800;
    } else if (this->symbol == JOLTEON) {
        // --/-- 雷雨 サンダース + かがくへんかガス
        return 6500;
    }
    
    return 5000;
}

void KNedoko23::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
