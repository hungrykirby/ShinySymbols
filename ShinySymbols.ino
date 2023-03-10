#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko23.h"
#include "y_tanren10.h"
#include "k_balllake12.h"
#include "k_mitsumata2.h"
#include "k_nedoko26.h"
#include "k_nedoko43.h"
#include "k_nedoko28.h"
#include "w_nakkuru_klang.h"
#include "k_suberidashi12.h"
#include "k_suberidashi8.h"
#include "y_tanren4.h"
#include "y_tanren3.h"

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
        case NIDOKING_NEDOKO43:
        case GRIMMSNARL:
        case NIDOQUEEN_NEDOKO43:
            {
                KNedoko43 pokemon = KNedoko43(target);
                pokemon.loop();
            }
            break;
        case GALVANTULA:
        case GLALIE:
        case ALTARIA:
        case BRONZONG:
        case ABSOL:
        case DUBWOOL:
        case DURANT:
        case CLEFABLE:
            {
                KNedoko28 pokemon = KNedoko28(target);
                pokemon.loop();
            }
            break;
        case KLANG_DROUGHT:
        case KLANG_SUNNY:
            {
                WNakkuruKlang pokemon = WNakkuruKlang(target);
                pokemon.loop();
            }
            break;
        case MAMOSWINE:
        case GLALIE_SUBERIDASHI:
        case SNORLAX:
        case JYNX:
        case CRYOGONAL_SUBERIDASHI:
        case WEAVILE:
            {
                KSuberidashi12 pokemon = KSuberidashi12(target);
                pokemon.loop();
            }
            break;
        case FLOSLASS:
        case MAGMORTAR:
        case SNOM:
        case HATENNA:
        case AMAURA:
            {
                KSuberidashi8 pokemon = KSuberidashi8(target);
                pokemon.loop();
            }
            break;
        case MAGNETON:
        case SWOOBAT:
        case FLETCHINDER:
        case SKARMORY:
        case DRIFBLIM:
            {
                YTanren4 p = YTanren4(target);
                p.loop();
            }
            break;
        case COMFEY:
        case CRUSTLE:
        case LUXIO:
        case SCYTHER:
        case KANGASKHAN:
        case DRAPION:
        case PELIPPER:
            {
                YTanren3 p = YTanren3(target);
                p.loop();
            }
            break;
            
    }

}
