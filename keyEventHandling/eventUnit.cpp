//
// Created by tomek on 30.07.2020.
//

#include "eventUnit.h"

eventUnit::eventUnit()
{
    mouseWheel=0;

}

void eventUnit::resetKey(buttons b)
{
    switch (b){
        case buttons::mouseLbutton:{
            mouseLbutton={0,0};
            break;
        }
        case buttons::mouseRbutton:{
            mouseRbutton={0,0};
            break;
        }
        case buttons::keyboardPbutton:{
            keyboard_P_button = {0, 0};
            break;
        }
        case buttons::keyboard_D_button:{
            keyboard_D_button={0,0};
            break;}

        case buttons::mouse_Wheel:{
            mouseWheel=0;
        }
        case buttons::keyboard_up:{
            keyboard_up={0,0};
            break;
        }
        case buttons::keyboard_down:{
            keyboard_down={0,0};
            break;
        }
        case buttons::keyboard_left:{
            keyboard_left={0,0};
            break;
        }
        case buttons::keyboard_right:{
            keyboard_right={0,0};
            break;
        }
        default:{
            mouseWheel=0;
            break;
        }

    }
}






