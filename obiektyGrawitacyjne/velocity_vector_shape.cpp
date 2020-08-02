//
// Created by tomek on 02.08.2020.
//

#include "velocity_vector_shape.h"


velocity_vector_shape::velocity_vector_shape(ObiektGrawitacyjny t)
{
    this->setOrigin(0,0);
    this->setPosition(x0.first,x0.second);
    x0=t.getCord();
    x1={x0.first+t.returnVelocity().first*LENGHT_COEFFICIENT,
        x0.second+t.returnVelocity().second*LENGHT_COEFFICIENT };
    setFillColor(sf::Color::White);
    setPointCount(4);
    if(t.velocity[0]!=0 || t.velocity[1]!=0 )
    {
        setPoint(0, sf::Vector2f(x0.first, x0.second));
        setPoint(1, sf::Vector2f(x1.first, x1.second));
        setPoint(2, sf::Vector2f(x1.first, x1.second + THICKNES_OF_VELOCITY_VECTOR));
        setPoint(3, sf::Vector2f(x0.first, x0.second + THICKNES_OF_VELOCITY_VECTOR));
    }
    else if(t.velocity[0]==0 || t.velocity[1]==0)
    {
        setPoint(0, {0,0});
        setPoint(1, {0,0});
        setPoint(2, {0,0});
        setPoint(3, {0,0});
    }



}
