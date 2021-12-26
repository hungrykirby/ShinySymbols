#include <auto_command_util.h>
#include "modules.h"
#include "k_nedoko23.h"

int target = SYLVEON;

void setup(){
    recogizeController();
}
void loop(){
    switch (target) {
        case SYLVEON:
            KNedoko23 sylveon = KNedoko23(target);
            sylveon.loop();
            break;
        case SCIZOR:
            loopScizor();
            break;
    }

}
