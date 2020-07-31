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
            keyboardPbutton = {0,0};
            break;
        }
        default:
        {
            break;
        }

    }
}






