#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko23.h"
#include "y_tanren10.h"
#include "k_balllake12.h"

int target;

void setup(){
    recogizeController();
    target = setTarget(); // ポケモンの定数をreturnしているだけ
}
void loop(){
    switch (target) {
        case SYLVEON:
        case ARAQUANID:
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
            
    }

}
