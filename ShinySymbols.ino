#include <auto_command_util.h>
#include "modules.h"

void setup(){
    myPush(Button::B, 500, 13);
}
void loop(){
    // loopSylveon();
    loopScizor();
}