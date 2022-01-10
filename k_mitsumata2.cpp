#include <auto_command_util.h>
#include "modules.h"
#include "k_mitsumata2.h"

/*
 * カンムリ雪原三つまたヶ原 固定シンボル2
 * ドラパルト、エレキブル
 * https://yakkun.com/swsh/map.htm?place=mitumata
 * 
 */


KMitsumata2::KMitsumata2(int pokemon) {
    this->symbol = pokemon;
}

// 移動パート①
void KMitsumata2::moveToInitialPlayerPosition(){
    openMap();

    myDelay(200);
    
    sky();
}

//　移動パート②～戦闘パート
void KMitsumata2::symbolEncount(){
    SwitchController().setStickTiltRatio(-12, -100, 0, 0);
    myDelay(1500); // 少し進む
    myPush(Button::LCLICK, 100, 15);
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
    myPushHatButton(Hat::UP, BUTTON_PUSHING_MSEC, 1000);
    myPushButton(Button::A, BUTTON_PUSHING_MSEC, 800);
    myPush(Button::B, 400, 2);
    myPushHatButton(Hat::UP, 1500, BUTTON_PUSHING_MSEC);
    myPush(Button::A, 800, 2);
    myPush(Button::B, 100, 5);
}

int KMitsumata2::convertToMSecFromPokemon() {
    if (this->symbol == DRAGAPULT_AME) {
        // 1/9 雨 ドラパルト ＋ かがくへんかガス
        return 5000;
    } else if (this->symbol == ELECTIVIRE) {
        // --/-- 雷雨 エレキブル + かがくへんかガス
        return 5500;
    }
    return 1500;
}

void KMitsumata2::loop() {
    this->moveToInitialPlayerPosition();
    this->symbolEncount();
    execTimeLeap();
}
