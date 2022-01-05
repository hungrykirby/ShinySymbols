#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko23.h"
#include "y_tanren10.h"

int target;

void setup(){
    recogizeController();
    target = WIGGLYTUFF;
}
void loop(){
    switch (target) {
        case SYLVEON:
            {
                KNedoko23 sylveon = KNedoko23(target);
                sylveon.loop();
            }
            break;
        case SCIZOR:
            {
                YTanren10 scizor = YTanren10(target);
                scizor.loop();
            }
            break;
        case KINGLER:
            {
                YTanren10 kingler = YTanren10(target);
                kingler.loop();
            }
            break;
        case LUXRAY:
            {
                YTanren10 luxray = YTanren10(target);
                luxray.loop();
            }
            break;
        case LILLIGANT:
            {
                YTanren10 lilligant = YTanren10(target);
                lilligant.loop();
            }
            break;
        case STOUTLAND:
            {
                YTanren10 stoutland = YTanren10(target);
                stoutland.loop();
            }
            break;
        case WIGGLYTUFF:
            {YTanren10 wigglytuff = YTanren10(target); wigglytuff.loop();}
            break;
            
    }

}
