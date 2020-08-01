//
// Created by tomek on 30.07.2020.
//

#ifndef GRAVITY_EVENTUNIT_H
#define GRAVITY_EVENTUNIT_H
#include <utility>

enum buttons{
    mouseLbutton,mouseRbutton,keyboardPbutton,keyboard_D_button,mouse_Wheel
};

struct eventUnit
{

        eventUnit();
        void resetKey(buttons b);

        //mose keys e
        std::pair<bool,bool> mouseLbutton;
        bool isMouseLbutton;

        std::pair<bool,bool> mouseRbutton;
        bool isMouseRbutton;

        std::pair<bool,bool> keyboard_P_button;
        std::pair<bool,bool> keyboard_D_button;

        //mose position
        std::pair<double,double> mouseCord;
        //mose wheel
        double mouseWheel;
};


#endif //GRAVITY_EVENTUNIT_H
