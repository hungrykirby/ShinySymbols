#include <auto_command_util.h>
#include "modules.h"

int pokemon = SCIZOR;

void setup(){
    recogizeController();
}
void loop(){
    switch (pokemon) {
        case SYLVEON:
            loopSylveon();
            break;
        case SCIZOR:
            loopScizor();
            break;
    }

}
