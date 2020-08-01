//
// Created by tomek on 01.08.2020.
//

#include "Game.h"
#include <limits>
void Game::resetBoolRepresentationOfCombination()
{
    if(obiektyGrawitacyjne.size()<2) return;
    if(obiektyGrawitacyjne.size()==2)
    {
     boolRepresentationOfCombination.resize(2);
     boolRepresentationOfCombination[0]=1;
     boolRepresentationOfCombination[1]=1;
    }
    boolRepresentationOfCombination.resize(obiektyGrawitacyjne.size());
    for(auto &obj:boolRepresentationOfCombination) obj=0;
    boolRepresentationOfCombination[boolRepresentationOfCombination.size()-1]=1;
    boolRepresentationOfCombination[boolRepresentationOfCombination.size()-2]=1;

}

ObiektGrawitacyjny *Game::locate_nearest_gravity_obj() {
    if(obiektyGrawitacyjne.empty()) return nullptr;
    if(obiektyGrawitacyjne.size()==1) return &obiektyGrawitacyjne[0];
    struct tempstruct{
        tempstruct(){temp= nullptr;distance=std::numeric_limits<double>::max();}
        ObiektGrawitacyjny *temp;
        double distance;
    };
    auto returnDistance=[&](int n){//returning distance between mose position and n object in vector obiektyGrawitacyjne
        if(n>obiektyGrawitacyjne.size()) throw std::out_of_range{"out of range\n"};
        return distanceBetween(obiektyGrawitacyjne[n],m_window.getEventUnit().mouseCord);
    };
    tempstruct tempory;
    for(auto i=0;i<obiektyGrawitacyjne.size();i++){
        double d=returnDistance(i);
        if(d<tempory.distance)
        {
            tempory.temp=&obiektyGrawitacyjne[i];
            tempory.distance=d;
        }
    }
    return tempory.temp;
}

double Game::returnDistanceMouseObj(ObiektGrawitacyjny obj) {
    return distanceBetween(obj,m_window.getEventUnit().mouseCord);
}