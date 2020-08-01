//
// Created by tomek on 22.07.2020.
//

#include <iostream>
#include "ObiektGrawitacyjny.h"

ObiektGrawitacyjny::ObiektGrawitacyjny(double x, double y, double weight_)
:sf::CircleShape(),force(2),velocity(2),cord(2)
{
    mass = weight_;
    force[(int)orientation::horizontal]=0;
    force[(int)orientation::vertical]=0;
    velocity[(int)orientation::horizontal]=0;
    velocity[(int)orientation::vertical]=0;
    cord[(int)orientation::horizontal]=x;
    cord[(int)orientation::vertical]=y;

    sf::CircleShape::setRadius(weight_/(125*M_PI));
//    sf::CircleShape::setRadius(10);
    sf::CircleShape::setPosition(x,y);
    sf::CircleShape::setFillColor(sf::Color::Red);
    sf::CircleShape::setOrigin({getRadius(),getRadius()});
}

vector<double> ObiektGrawitacyjny::returnVersor(const ObiektGrawitacyjny &obg)
{
    vector<double> vect(2);
    vect[(int)orientation::horizontal] = obg.cord[(int)orientation::horizontal] - cord[(int)orientation::horizontal];
    vect[(int)orientation::vertical] = obg.cord[(int)orientation::vertical] - cord[(int)orientation::vertical];
    double lenghtOfVector = sqrt(pow(vect[(int)orientation::horizontal],2)+pow(vect[(int)orientation::vertical],2));
    vect[(int)orientation::horizontal] = vect[(int)orientation::horizontal]/lenghtOfVector;
    vect[(int)orientation::vertical] = vect[(int)orientation::vertical]/lenghtOfVector;
    return std::move(vect);
}

pair<double, double> ObiektGrawitacyjny::getCord() {
    return pair<double, double>(
            cord[(int)orientation::horizontal],
            cord[(int)orientation::vertical]
            );
}

pair<double, double> ObiektGrawitacyjny::returnVersorAsPair(const ObiektGrawitacyjny &obg) {
    vector<double> vect(2);
    vect[(int)orientation::horizontal] = obg.cord[(int)orientation::horizontal] - cord[(int)orientation::horizontal];
    vect[(int)orientation::vertical] = obg.cord[(int)orientation::vertical] - cord[(int)orientation::vertical];
    double lenghtOfVector = sqrt(pow(vect[(int)orientation::horizontal],2)+pow(vect[(int)orientation::vertical],2));
    vect[(int)orientation::horizontal] = vect[(int)orientation::horizontal]/lenghtOfVector;
    vect[(int)orientation::vertical] = vect[(int)orientation::vertical]/lenghtOfVector;
    return pair<double, double>(vect[(int)orientation::horizontal],vect[(int)orientation::vertical]);
}

double returnForce(ObiektGrawitacyjny a, ObiektGrawitacyjny b)
{

    return 0;
}

double distanceBetween(ObiektGrawitacyjny  & ob1,ObiektGrawitacyjny  & ob2) {
    double a = ob1.cord[0]- ob2.cord[0];
    double b = ob1.cord[1]- ob2.cord[1];
    return sqrt(pow(a,2)+pow(b,2));
}

double returnForce(ObiektGrawitacyjny &a, ObiektGrawitacyjny &b) {
    double r =  distanceBetween(a,b),
                G=1,
                m1=a.mass,
                m2=a.mass;
    return G*m1*m2/pow(r,2);

}


void ObiektGrawitacyjny::setForce(double force,  pair<double,double> &versor)
{
    this->force[0] = force*versor.first;
    this->force[1] = force*versor.second;
}

pair<double, double> ObiektGrawitacyjny::returnForce(void) {
    return pair<double, double>(force[0],force[1]);
}

pair<double, double> ObiektGrawitacyjny::returnVelocity(void) {
    return pair<double, double>(velocity[0],velocity[1]);
}

void ObiektGrawitacyjny::increseVelocity(pair<double, double> deltaV)
{
    velocity[0]+=deltaV.first;
    velocity[1]+=deltaV.second;
}


double ObiektGrawitacyjny::returnMass() {
    return mass;
}

void ObiektGrawitacyjny::setCord(pair<double,double> const& deltaCord)
{
    cord[0]=deltaCord.first;
    cord[1]=deltaCord.second;
    sf::CircleShape::setPosition(cord[0],cord[1]);
}

void ObiektGrawitacyjny::increseCord(pair<double, double> &deltaCord)
{
    cord[0]+=deltaCord.first;
    cord[1]+=deltaCord.second;
    sf::CircleShape::setPosition(cord[0],cord[1]);
}

void ObiektGrawitacyjny::setVelocity(pair<double, double> v)
{
    velocity[0] = v.first;
    velocity[1] = v.second;
}

void ObiektGrawitacyjny::setMass(double mass_)
{
    mass = mass_;
}

ObiektGrawitacyjny::ObiektGrawitacyjny(double x, double y, double weight_, pair<double, double> velocity)
:ObiektGrawitacyjny(x,y,weight_)
{
    this->velocity[0]=velocity.first;
    this->velocity[1]=velocity.second;
}

bool ObiektGrawitacyjny::operator==(const ObiektGrawitacyjny &ob) const {
    return this->mass == ob.mass &&
           this->cord[0] == ob.cord[0] &&
           this->cord[1] == ob.cord[1];
}

double distanceBetween(ObiektGrawitacyjny &ob1, pair<double, double> mose_position)
{
    double d1 = ob1.getCord().first - mose_position.first;
    double d2= ob1.getCord().second - mose_position.second;
    return sqrt(pow(d1,2)+pow(d2,2));
}

double countMinimalDistanceToMarge(const ObiektGrawitacyjny &a, const ObiektGrawitacyjny &b) {
    return a.getRadius() + b.getRadius();
}







