#include <iostream>
#include "Game.h"
#include "ObiektGrawitacyjny.h"
Game::Game(): m_window("Chapter 2", sf::Vector2u(2000,2000)){
	RestartClock();
	srand(time(NULL));




	// setting gravity object
    obiektyGrawitacyjne.push_back({1000+100,1000,5000});
    obiektyGrawitacyjne[0].setVelocity({0,2});
    obiektyGrawitacyjne.push_back({1000-100,1000,5000});
    obiektyGrawitacyjne[1].setVelocity({0,-2});

    //setting representation of combination of 2 gravity object
    for(int i=0;i<obiektyGrawitacyjne.size();i++)
        boolRepresentationOfCombination.push_back(0);
    boolRepresentationOfCombination[boolRepresentationOfCombination.size()-1]=1;
    boolRepresentationOfCombination[boolRepresentationOfCombination.size()-2]=1;
    //

}

Game::~Game(){ }

sf::Time Game::GetElapsed(){ return m_elapsed; }
void Game::RestartClock(){ m_elapsed = m_clock.restart(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::HandleInput(){
	// Input handling.
}

void Game::Update(){
	m_window.Update();

	//obliczanie wszystkich versorow miedzy wszystkimi mozliwymi parami obiektow grawitacyjnych
	//chyba zrezygnuje z tej sekcji i bede je obliczac na biezaco
    for(auto i=0;i<obiektyGrawitacyjne.size();i++)
    {
        for(auto j=0;j<obiektyGrawitacyjne.size();j++)
        {
            if(i==j) continue;
            pair<double,double> pair1 = obiektyGrawitacyjne[i].returnCord();
            pair<double,double> pair2 = obiektyGrawitacyjne[j].returnCord();
            versorMap[pair(pair1,pair2)]=obiektyGrawitacyjne[i].returnVersorAsPair(obiektyGrawitacyjne[j]);
        }
    }

    //obliczanie sily pomiedzy wszystkimi parami obiektow, nadawanie im tych sil odzialywan
    if(obiektyGrawitacyjne.size()>1)
    do{
        pair<int,int> vectorSubscripts = returnSubscriptsForPairInVector(boolRepresentationOfCombination);
        double force_ = returnForce(obiektyGrawitacyjne[vectorSubscripts.first],obiektyGrawitacyjne[vectorSubscripts.second]);
        ObiektGrawitacyjny &obiektGrawitacyjny1 = obiektyGrawitacyjne[vectorSubscripts.first];
        ObiektGrawitacyjny &obiektGrawitacyjny2 = obiektyGrawitacyjne[vectorSubscripts.second];
        pair<double,double> cord1 = obiektGrawitacyjny1.returnCord();
        pair<double,double> cord2 = obiektGrawitacyjny2.returnCord();
        //cord1 -> cord2 vector
        pair<double, double> &versordC1C2 = versorMap[pair(cord1, cord2)];
        //cord2 -> cord1 vector
        pair<double, double> &versorC2C1 = versorMap[pair(cord2, cord1)];
        obiektGrawitacyjny1.setForce(force_,versordC1C2);
        obiektGrawitacyjny2.setForce(force_,versorC2C1);
    }while(std::next_permutation(boolRepresentationOfCombination.begin(),boolRepresentationOfCombination.end()));
    resetRepresentationOfCombination(boolRepresentationOfCombination);

   //obliczanie delta vector predkosci i dodawanie ich do aktualnie posiadanych wektorow
   //przesuwanie obiektow na podstawie wektora predkosci
   for(auto it=obiektyGrawitacyjne.begin();it!=obiektyGrawitacyjne.end();it++) {
       //obliczanie predkosci
       double deltaVelocityHorizontal = it->returnForce().first * DELTA_TIME_PER_TICK_ / it->returnMass(),
               deltaVelocityVertical = it->returnForce().second * DELTA_TIME_PER_TICK_ / it->returnMass();
       pair<double, double> deltaVelocityHorizontalVertical{deltaVelocityHorizontal, deltaVelocityVertical};
       it->increseVelocity(deltaVelocityHorizontalVertical);

       //obliczanie przemieszczen
       double deltaCordHorizontal = it->returnVelocity().first * DELTA_TIME_PER_TICK_;
       double deltaCordVertical = it->returnVelocity().second * DELTA_TIME_PER_TICK_;
       pair<double,double> deltaCordVector{deltaCordHorizontal,deltaCordVertical};
       it->increseCord(deltaCordVector);
   }

   //scalanie obiektow bedacych odpowiednio blisko
   if(obiektyGrawitacyjne.size()>1)
   do{
        pair<int,int> vectorSubscripts = returnSubscriptsForPairInVector(boolRepresentationOfCombination);
        double distance = distanceBetween(obiektyGrawitacyjne[vectorSubscripts.first],obiektyGrawitacyjne[vectorSubscripts.second]);
        if(distance<=MINIMAL_DISTANCE_TO_MERGE)
        {
            ObiektGrawitacyjny ob1 = obiektyGrawitacyjne[vectorSubscripts.first];
            ObiektGrawitacyjny ob2 = obiektyGrawitacyjne[vectorSubscripts.second];
            double  sumofmass=ob1.returnMass()+ob2.returnMass(),
                    coefficient1=ob1.returnMass()/sumofmass,
                    coefficient2=ob2.returnMass()/sumofmass;
            pair<double,double> velocitySum{ob1.returnVelocity().first*coefficient1+ob2.returnVelocity().first*coefficient2,
                                            ob1.returnVelocity().second*coefficient1+ob2.returnVelocity().second*coefficient2};
            obiektyGrawitacyjne.push_back(ObiektGrawitacyjny{ob1.returnCord().first,ob1.returnCord().second,sumofmass,velocitySum});
            obiektyGrawitacyjne.erase(obiektyGrawitacyjne.begin()+vectorSubscripts.first);
            auto iteratorToSecondToDelete = std::find(obiektyGrawitacyjne.begin(),obiektyGrawitacyjne.end(),ob2);
            if(iteratorToSecondToDelete!=obiektyGrawitacyjne.end())
                obiektyGrawitacyjne.erase(iteratorToSecondToDelete);
            boolRepresentationOfCombination.empty();
            boolRepresentationOfCombination.resize(obiektyGrawitacyjne.size());
            resetRepresentationOfCombination(boolRepresentationOfCombination);
        }
    }while(std::next_permutation(boolRepresentationOfCombination.begin(),boolRepresentationOfCombination.end()));
    resetRepresentationOfCombination(boolRepresentationOfCombination);


}


void Game::Render(){
	m_window.BeginDraw(); // Clear.

    for(auto &obj:obiektyGrawitacyjne)
        m_window.Draw(obj);

	m_window.EndDraw(); // Display.
}