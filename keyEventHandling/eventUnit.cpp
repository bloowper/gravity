//
// Created by tomek on 30.07.2020.
//

#include "eventUnit.h"

eventUnit::eventUnit()
{

}

void eventUnit::resetKey(buttons b)
{
    switch (b)
    {
        case buttons::mouseLbutton:
        {
            mouseLbutton={0,0};
            break;
        }
        case buttons::mouseRbutton:
        {
            mouseRbutton={0,0};
            break;
        }
        case buttons::keyboardPbutton:
        {
            keyboard_P_button = {0, 0};
            break;
        }
        case buttons::keyboard_D_button:
        {
            keyboard_D_button={0,0};
            break;
        }
        default:
        {
            break;
        }

    }
}






