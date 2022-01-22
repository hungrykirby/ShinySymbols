#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko23.h"
#include "y_tanren10.h"
#include "k_balllake12.h"
#include "k_mitsumata2.h"
#include "k_nedoko26.h"

int target;

void setup(){
    recogizeController();
    target = setTarget(); // ポケモンの定数をreturnしているだけ
}
void loop(){
    switch (target) {
        case SYLVEON:
        case ARAQUANID:
        case NIDOKING_NEDOKO23:
        case JOLTEON: // オニシズクモが飛び出してくるため精度が低い。ループ破綻はしない。
            {
                KNedoko23 pokemon = KNedoko23(target);
                pokemon.loop();
            }
            break;
        case SCIZOR:
        case KINGLER:
        case LUXRAY:
        case LILLIGANT:
        case STOUTLAND:
        case WIGGLYTUFF:
        case BISHARP:
            {
                YTanren10 pokemon = YTanren10(target);
                pokemon.loop();
            }
            break;
        case ARON_RAIU:
            {
                KBalllake12 pokemon = KBalllake12(target);
                pokemon.loop();
            }
            break;
        case DRAGAPULT_AME:
        case ELECTIVIRE:
            {
                KMitsumata2 pokemon = KMitsumata2(target);
                pokemon.loop();
            }
            break;
        case UMBREON:
        case NIDORINA:
        case ELECTABUZZ:
        case HEATMOR:
        case CRYOGONAL:
        case LEAFEON:
            {
                KNedoko26 pokemon = KNedoko26(target);
                pokemon.loop();
            }
            break;
            
    }

}
