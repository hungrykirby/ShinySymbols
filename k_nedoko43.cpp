#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko43.h"

KNedoko43::KNedoko43(int pokemon) {
    this->symbol = pokemon;
}

void KNedoko43::moveToInitialPlayerPosition() {
    openMap();
    myPushHatButton(Hat::RIGHT_DOWN, 180, BUTTON_PUSHING_MSEC);
    myPushHatButton(Hat::RIGHT, 80, BUTTON_PUSHING_MSEC);
    myDelay(200);
    sky();
}

void KNedoko43::symbolEncount() {
    SwitchController().setStickTiltRatio(-5, -100, 0, 0);
    myDelay(1500); // 少し進む
    myPush(Button::LCLICK, 100, 5);
    myDelay(2000); // 鳴らし始める
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
    // 戦闘開始～「たたかう」が表示されるまで待機。
    // 下の時間は、使用する言語、ポケモン等で多少ずれる可能性があり、delay要調整
    // 色違いのエフェクトが約2秒のため、「たたかう」が表示されて2秒以内に次の十字上↑入力がされるようにする
    myPush(Button::A, 200, 4);
    myPush(Button::B, 200, 8);

    myDelay(this->convertToMSecFromPokemon());
    myPush(Button::B, 200, 5);
    // 戦闘開始、色違い光モーションなければ十字上＞逃げる
    // 色違いならば、1つめの上入力間に合わないため戦闘＞自爆技で自分側瀕死
    // Aボタンを2回以上連続して押す場合は、次のポケモン選択画面で一番上以外のポケモンを繰り出さないようにする
    myPushHatButton(Hat::UP, BUTTON_PUSHING_MSEC, 2100);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 800);
    myPush(Button::B, 400, 2);
    myPushHatButton(Hat::UP, 1500, BUTTON_PUSHING_MSEC);
    myPush(Button::A, 800, 2);
    myPush(Button::B, 100, 5);

    // そのままいるとオニシズクモに見つかって戦闘になることがあるため草むらから遠ざかる
    SwitchController().setStickTiltRatio(-100, 100, -50, 0);
    myDelay(BUTTON_PUSHING_MSEC);
    myPushButton(Button::B, BUTTON_PUSHING_MSEC, 1000);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
}

int KNedoko43::convertToMSecFromPokemon() {
    if (this->symbol == NIDOKING_NEDOKO43) {
        // 1/30 雨 ニドキング ＋ かがくへんかガス
        return 6500;
    } else if (this->symbol == GRIMMSNARL) {
        // 1/17 霧 オーロンゲ + かがくへんかガス
        return 6500;
    }
    return 1500;
}

void KNedoko43::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}