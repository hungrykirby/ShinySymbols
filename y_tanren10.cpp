#include <auto_command_util.h>
#include "modules.h"
#include "y_tanren10.h"

// ヨロイの孤島 鍛錬平原 固定シンボル10
// ハッサム（砂嵐）、キングラー（雨）など
// https://yakkun.com/swsh/map.htm?place=tanren

YTanren10::YTanren10(int pokemon) {
    this->symbol = pokemon;
}

// 移動パート①
void YTanren10::moveToInitialPlayerPosition(){
    openMap();

    myPushHatButton(Hat::UP_RIGHT, 60, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
}

//　移動パート②～戦闘パート
void YTanren10::symbolEncount(){

    // ワット掘り出しおやじ付近
    myTiltJoystick(100, 0, 0, 0, 100, 30);
    myTiltJoystick(0, 100, 0, 0, 3500, 30);

    SwitchController().setStickTiltRatio(2, 100, 0, 0);
    myDelay(100);
    for(int i = 0; i < 11; i++){
        SwitchController().pressButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
        SwitchController().releaseButton(Button::LCLICK);
        myDelay(BUTTON_PUSHING_MSEC);
    }
    myDelay(100);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

    myDelay(100);

    // エンカウントできなかった際に遠ざかる
    SwitchController().setStickTiltRatio(100, -50, 0, 0);
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
}

int YTanren10::convertToMSecFromPokemon() {
    if (this->symbol == SCIZOR) {
        // 12-11 すなあらし ハッサム ＋ かがくへんかガス
        return 5800;
    } else if (this->symbol == KINGLER || this->symbol == WIGGLYTUFF) {
        // 1/2 雨 キングラー + かがくへんかガス
        // 1/1 霧 プクリン + かがくへんかガス
        return 5400;
    } else if (this->symbol == LILLIGANT) {
        // 12/24 日照 ドレディア + かがくへんかガス
        return 5500;
    } else if (this->symbol == LUXRAY) {
        // 12/31 雷雨 レントラー + かがくへんかガス
        return 6500;
    } else if (this->symbol == STOUTLAND) {
        // 1/4 晴れ（なし） ムーランド + かがくへんかガス
        return 5000;
    } else if (this->symbol == BISHARP) {
        // 1/16 曇り（なし） キリキザン + かがくへんかガス
        return 5000;
    } else {
        return 5000;
    }
    return 0;
}

void YTanren10::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
