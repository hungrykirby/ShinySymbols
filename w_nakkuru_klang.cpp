// ワイルドエリア ナックル丘陵 固定シンボルギギアル？
// https://yakkun.com/swsh/map.htm?place=nakkuru_kyuryo

#include <auto_command_util.h>
#include "modules.h"
#include "w_nakkuru_klang.h"

WNakkuruKlang::WNakkuruKlang(int pokemon) {
    this->symbol = pokemon;
}

void WNakkuruKlang::moveToInitialPlayerPosition() {
    openMap();

    //カーソルを飛ぶ場所に合わせる

    myDelay(200);
    
    sky();
}

void WNakkuruKlang::symbolEncount() {
    myDelay(300);
    myTiltJoystick(0, 0, 100, 0, 930, 100);
    myDelay(400);
    myTiltJoystick(0, -100, 0, 0, 3000, 200);

    SwitchController().setStickTiltRatio(0, -100, 0, 0);
    myPush(Button::B, 100);
    myDelay(2300);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);
    myDelay(50);

    SwitchController().setStickTiltRatio(-7, -100, 0, 0);
    myPush(Button::LCLICK, 100, 10);
    myDelay(300);
    SwitchController().setStickTiltRatio(0, 0, 0, 0);

    myTiltJoystick(100, 80, 0, 0, 1000, 50);
    myTiltJoystick(70, 100, 0, 0, 1000, 50);
    myTiltJoystick(20, 100, 0, 0, 1000, 50);

    myPush(Button::A, 200, 2);
    myPush(Button::B, 200, 5);
    // ガラルマタドガス（かがくへんか）がいると特性が発動しないため精度が上がる。
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

int WNakkuruKlang::convertToMSecFromPokemon() {
    //ギギアルの動きが大きいので比較的ここに余裕を持たせないときつい
    // 少し余裕目のほうがいい
    if (this->symbol == 0) {
        // かがくへんかガス
        return 4500;
    } else if (this->symbol == KLANG_DROUGHT) {
        // 日照り＋かがくへんかガス
        return 5500;
    }
    return 4500;
}

void WNakkuruKlang::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
