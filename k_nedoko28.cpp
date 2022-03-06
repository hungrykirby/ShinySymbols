// カンムリ雪原 巨人の寝床 固定シンボル28
// デンチュラ（雷雨）など
// https://yakkun.com/swsh/map.htm?place=nedoko

#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko28.h"

KNedoko28::KNedoko28(int pokemon) {
    this->symbol = pokemon;
}

void KNedoko28::moveToInitialPlayerPosition() {
    openMap();

    //カーソルを飛ぶ場所に合わせる
    myPushHatButton(Hat::UP_RIGHT, 110, BUTTON_PUSHING_MSEC);
    myPushHatButton(Hat::RIGHT, 80, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
}

void KNedoko28::symbolEncount() {
    // そらを飛ぶ地点から直接ポケモンに当たると
    // 雪中渓谷の天気が反映されるためそれを避けるために
    // いったん巣穴近くの木まで移動する
    myTiltJoystick(-100, 0, 0, 0, 2500, 30);
    myTiltJoystick(-9, -100, 0, 0, 1300, 30);
    myTiltJoystick(10, -100, 0, 0, 2000, 30);
    myTiltJoystick(10, 100, 0, 0, 300, 30);
    myTiltJoystick(0, 100, 0, 0, 1000, 30);
    myTiltJoystick(70, 100, 0, 0, 600, 30);
    myTiltJoystick(100, 90, 0, 0, 1000, 30);
    myTiltJoystick(100, 30, 0, 0, 600, 30);
    myTiltJoystick(100, 85, 0, 0, 600, 30);
    myTiltJoystick(0, 100, 0, 0, 950, 30);

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

int KNedoko28::convertToMSecFromPokemon() {
    if (this->symbol == GALVANTULA) {
        // 雨＋エレキフィールド＋かがくへんかガス
        return 7500;
    } else if (this->symbol == GLALIE) {
        // 雪＋かがくへんかガス
        return 6500;
    } else if (this->symbol == ALTARIA) {
        // かがくへんかガス
        return 6000;
    } else if (this->symbol == BRONZONG) {
        // 雨＋かがくへんかガス
        return 6500;
    } else if (this->symbol == ABSOL) {
        // 雪＋かがくへんかガス
        return 6500;
    } else if (this->symbol == DUBWOOL) {
        // かがくへんかガス
        return 6000;
    } else if (this->symbol == DURANT) {
        // 日照＋かがくへんかガス
        return 6500;
    } else if (this->symbol == CLEFABLE){
        // 霧＋かがくへんかガス
        return 6500;
    }
    return 5500;
}

void KNedoko28::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
