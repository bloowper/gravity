//
// Created by tomek on 02.08.2020.
//

#ifndef GRAVITY_VELOCITY_VECTOR_SHAPE_H
#define GRAVITY_VELOCITY_VECTOR_SHAPE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "ObiektGrawitacyjny.h"
const double LENGHT_COEFFICIENT = 10;
const double THICKNES_OF_VELOCITY_VECTOR = 1;

class velocity_vector_shape:
public sf::ConvexShape
{
    public:
        velocity_vector_shape(ObiektGrawitacyjny t);
    private:
        std::pair<double,double> x0;
        std::pair<double,double> x1;
};


#endif //GRAVITY_VELOCITY_VECTOR_SHAPE_H
