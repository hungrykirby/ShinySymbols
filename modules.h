#ifndef MODULES_H
#define MODULES_H

void myDelay(int delay_ms, unsigned long method_start_ms = -1);
void recogizeController();
// bool myDelayOne(int delay_ms);
bool myPush(Button b, int d, int count = 1);
// bool myPushCount(Button b, int d, int count);
bool myPushButton(Button button, int holdtime, int delay_time_ms);
bool myPushHatButton(Hat button, int holdtime, int delay_time_ms);
bool myTiltJoystick(int lx_per, int ly_per, int rx_per, int ry_per, int tilt_time_msec, int delay_time_ms);
void openMap();
void sky();
void execTimeLeap();
void changeTimeAtHome(int mode);
void runToSuana();
void initPosFromSuana();
void suanaTimeLeap(int goorback);

const uint16_t BUTTON_PUSHING_MSEC = 95;

/*
TIME_LEAP_MODE は時渡りバグを使うときの方法
1 がランクマバグを使用する。ランクマバグはいちいちランクバトルをするためすこしめんどくさい
（未定）2 が巣穴の「みんなで」から時渡りする方法。ワットがたまっていいが空を飛ぶスポットが変わるのでコードの分岐が発生する
（未定）3 がキャンプによる時渡り。
*/
#define RANKBATTLE 1
#define SUANA 2
#define CAMP 3

#define SYLVEON 1
#define SCIZOR 2
#define KINGLER 3
#define LUXRAY 4
#define LILLIGANT 5
#define STOUTLAND 6
#define WIGGLYTUFF 7
#define ARON_RAIU 8 // ココドラ（雷雨）
#define ARAQUANID 9 // オニシズクモ
#define DRAGAPULT_AME 10
#define ELECTIVIRE 11
#define NIDOKING_NEDOKO23 12 // ニドキング
#define JOLTEON 13 // サンダース
#define BISHARP 14 // キリキザン
#define UMBREON 15 // ブラッキー
#define NIDORINA 16 // ニドリーナ（霧）
#define ELECTABUZZ 17 // エレブー（雷雨）
#define HEATMOR 18 // クイタラン（日照）
#define CRYOGONAL 19 // フリージオ（雪）
#define LEAFEON 20 // リーフィア（晴れ）

const int TIME_LEAP_MODE = RANKBATTLE;

#endif
