/*
 * カンムリ雪原ボールレイクの湖畔 固定シンボル12
 * ココドラ
 * https://yakkun.com/swsh/map.htm?place=ball_lake
 * 
 * （注意）湖畔の洞窟にいる状態で始めてください
 * 
 */

#include <auto_command_util.h>
#include "modules.h"
#include "k_balllake12.h"

KBalllake12::KBalllake12(int pokemon) {
    this->symbol = pokemon;
}

// 移動パート①
// 湖畔の洞窟 -> ダイ木の丘
void KBalllake12::moveToInitialPlayerPosition(){
    openMap();

    myPushHatButton(Hat::DOWN_LEFT, 230, BUTTON_PUSHING_MSEC);

    myDelay(200);
    
    sky();
}

//　移動パート②～戦闘パート
void KBalllake12::symbolEncount(){

    myTiltJoystick(0, -100, 0, 0, 500, 30);
    myTiltJoystick(0, -100, -25, 0, 2200, 30);

    myTiltJoystick(0, -100, 0, 0, 4500, 30);

    // エンカウントできなかった場合、その位置から遠のく（洞窟に入る）
    SwitchController().setStickTiltRatio(0, -100, 0, 0);
    myDelay(BUTTON_PUSHING_MSEC);
    SwitchController().pressButton(Button::B);
    myDelay(BUTTON_PUSHING_MSEC);
    SwitchController().releaseButton(Button::B);
    myDelay(500);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

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
    myPush(Button::A, 700, 2);
    myPush(Button::B, 100, 5);

    myDelay(200);

    // 戦闘が終わった後遠ざかる（洞窟に入る）
    SwitchController().setStickTiltRatio(-50, -100, 0, 0);
    myDelay(BUTTON_PUSHING_MSEC);
    SwitchController().pressButton(Button::B);
    myDelay(BUTTON_PUSHING_MSEC);
    SwitchController().releaseButton(Button::B);
    myDelay(1300);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
}

int KBalllake12::convertToMSecFromPokemon() {
    if (this->symbol == ARON_RAIU) {
        // 雷雨（雨＋エレキフィールド） + ココドラ ＋ かがくへんかガス
        return 9000;
    }
    return 9000;
}

void KBalllake12::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
