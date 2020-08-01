//
// Created by tomek on 22.07.2020.
//

#ifndef GRAVITY_OBIEKTGRAWITACYJNY_H
#define GRAVITY_OBIEKTGRAWITACYJNY_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;

enum class orientation{
    horizontal=0,vertical
};

enum orient{
    horizontal=0,vertical
};

static const  double DELTA_TIME_PER_TICK_ = 0.1;
    static const double MINIMAL_DISTANCE_TO_MERGE =10;

class ObiektGrawitacyjny: public sf::CircleShape
{
    public:
        ObiektGrawitacyjny(double x,double y,double weight_);
        ObiektGrawitacyjny(double x,double y,double weight_,pair<double,double> velocity);
        bool operator==(const ObiektGrawitacyjny &ob) const;
        void setForce(double force,pair<double,double>  &versor);
        void increseVelocity(pair<double, double> deltaV);
        void setVelocity(pair<double,double> v);
        void setCord(pair<double,double> const& deltaCord);
        void setMass(double mass_);
        void increseCord(pair<double,double>& deltaCord);
        vector<double> returnVersor(ObiektGrawitacyjny const & obg);
        pair<double,double> returnVersorAsPair(ObiektGrawitacyjny const & obg);
        pair<double,double> getCord();
        pair<double,double> returnForce(void);
        pair<double,double> returnVelocity(void);
        double returnMass();
        friend double distanceBetween(ObiektGrawitacyjny  & ob1,ObiektGrawitacyjny  & ob2);
        friend double distanceBetween(ObiektGrawitacyjny &ob1,pair<double,double> mose_position);
        friend double returnForce(ObiektGrawitacyjny &a,ObiektGrawitacyjny &b);
//        friend double countMinimalDistanceToMarge(ObiektGrawitacyjny const  &a,ObiektGrawitacyjny const &b);

    private:
        double mass;
        vector<double> force;
        vector<double> velocity;
        vector<double> cord;

};


#endif //GRAVITY_OBIEKTGRAWITACYJNY_H
