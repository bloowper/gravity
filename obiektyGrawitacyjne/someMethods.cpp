//
// Created by tomek on 23.07.2020.
//

#include <iostream>
#include <algorithm>
#include "someMethods.h"

void resetRepresentationOfCombination(vector<int> &combination)
{
    for(auto it=combination.begin();it!=combination.end();it++)
        *it=0;
    combination[combination.size()-1]=1;
    combination[combination.size()-2]=1;
}

pair<int, int> returnSubscriptsForPairInVector(vector<int> &combination) {
    if(combination.size()==2)
        return {0,1};
    int to_return[2];
    int i=0;
    for(auto j=0;j<combination.size();j++)
    {
        if(combination[j])
        {
            to_return[i]=j;
            i++;
            if(i==2)
                break;
        }
    }
    return pair<int, int>(to_return[0],to_return[1]);
}







