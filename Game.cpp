#include <iostream>
#include "Game.h"
#include "ObiektGrawitacyjny.h"
Game::Game(): m_window("Chapter 2", sf::Vector2u(2000,2000)){
	RestartClock();
	srand(time(NULL));
    pause=false;

	// setting gravity object(start position for some of)
        obiektyGrawitacyjne.push_back({1000+95,1000,5000+200});
        obiektyGrawitacyjne[0].setVelocity({0,2});
        obiektyGrawitacyjne.push_back({1000-95,1000,5000+200});
        obiektyGrawitacyjne[1].setVelocity({0,-2});

        obiektyGrawitacyjne.push_back({1000+500,1000+500,1500});
        obiektyGrawitacyjne[2].setVelocity({-1,-1});
        obiektyGrawitacyjne.push_back({1000-500,1000-500,1500});
        obiektyGrawitacyjne[3].setVelocity({1,-1});
        obiektyGrawitacyjne.push_back({1000-500,1000+500,1500});
        obiektyGrawitacyjne[4].setVelocity({2,-2});
        obiektyGrawitacyjne.push_back({1000+500,1000-500,1500});
        obiektyGrawitacyjne[5].setVelocity({-1,-1});

    //setting representation of combination of 2 gravity object
    if(obiektyGrawitacyjne.size()>=2)
    {
        for (int i = 0; i < obiektyGrawitacyjne.size(); i++)
            boolRepresentationOfCombination.push_back(0);
        boolRepresentationOfCombination[boolRepresentationOfCombination.size() - 1] = 1;
        boolRepresentationOfCombination[boolRepresentationOfCombination.size() - 2] = 1;
    }
    //
    //setting new possible ObiektGrawitacyjny
    nowyObiektGrawitacyjny.push_back({ObiektGrawitacyjny{1, 1, 7000}, false});
}

Game::~Game(){ }

sf::Time Game::GetElapsed(){ return m_elapsed; }
void Game::RestartClock(){ m_elapsed = m_clock.restart(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::HandleInput(){
	// Input handling.
    eventUnit &eventUnit=m_window.getEventUnit();
//P button
    if(eventUnit.keyboard_P_button == pair<bool,bool>{1, 1})
    {
        pause = (!pause);
        eventUnit.resetKey(buttons::keyboardPbutton);
    }
//keyboard D button
    if(eventUnit.keyboard_D_button.first)
    {//D pressed

        if(eventUnit.keyboard_D_button.second)
        {//D relesed
            obiektyGrawitacyjne.clear();
            Game::resetBoolRepresentationOfCombination();
            eventUnit.resetKey(buttons::keyboard_D_button);
        }
    }
//mouse rbutton button
    if(eventUnit.mouseRbutton.first)
    {//pressed
        ObiektGrawitacyjny *obj = locate_nearest_gravity_obj();
        double tolarce_for_click =5;
        if(eventUnit.mouseRbutton.second)
        {//relesed
            if(obj!= nullptr && returnDistanceMouseObj(*obj)<=obj->getRadius()+tolarce_for_click) {
                {
                    const vector<ObiektGrawitacyjny>::iterator &iterator = std::find(obiektyGrawitacyjne.begin(),obiektyGrawitacyjne.end(), *obj);
                    if(iterator!=obiektyGrawitacyjne.end())
                    obiektyGrawitacyjne.erase(iterator);
                }
            }
            eventUnit.resetKey(buttons::mouseRbutton);
        }
    }
//mouse left button
    if(eventUnit.mouseLbutton.first)
    {//pressed

        nowyObiektGrawitacyjny[0].second=true;
        nowyObiektGrawitacyjny[0].first.setCord(eventUnit.mouseCord);
        if(eventUnit.mouseLbutton.second)
        {//relesed
            nowyObiektGrawitacyjny[0].second=false;
            obiektyGrawitacyjne.push_back(nowyObiektGrawitacyjny[0].first);
            resetBoolRepresentationOfCombination();
            eventUnit.resetKey(buttons::mouseLbutton);
        }
    }
//mose Wheel
    if(eventUnit.mouseWheel!=0)
    {
        double tolerance_mouse_distance=10;
        double mass_increase_value=200;
        ObiektGrawitacyjny *obj = locate_nearest_gravity_obj();
        if(obj!= nullptr)
        {
            if(returnDistanceMouseObj(*obj)<=obj->getRadius()+tolerance_mouse_distance)
            obj->increeseMass(mass_increase_value*eventUnit.mouseWheel);
        }
        m_window.getEventUnit().resetKey(buttons::mouse_Wheel);
    }
}

void Game::Update()
{
	m_window.Update();
	if(!pause)
    {
        resetBoolRepresentationOfCombination();
//obliczanie wszystkich versorow miedzy wszystkimi mozliwymi parami obiektow grawitacyjnych
        //chyba zrezygnuje z tej sekcji i bede je obliczac na biezaco
        for (auto i = 0; i < obiektyGrawitacyjne.size(); i++) {
            for (auto j = 0; j < obiektyGrawitacyjne.size(); j++) {
                if (i == j) continue;
                pair<double, double> pair1 = obiektyGrawitacyjne[i].getCord();
                pair<double, double> pair2 = obiektyGrawitacyjne[j].getCord();
                versorMap[pair(pair1, pair2)] = obiektyGrawitacyjne[i].returnVersorAsPair(obiektyGrawitacyjne[j]);
            }
        }

//obliczanie sily pomiedzy wszystkimi parami obiektow, nadawanie im tych sil odzialywan
        if (obiektyGrawitacyjne.size() > 1)
            do
            {
                pair<int, int> vectorSubscripts = returnSubscriptsForPairInVector(boolRepresentationOfCombination);
                double force_ = returnForce(obiektyGrawitacyjne[vectorSubscripts.first],
                                            obiektyGrawitacyjne[vectorSubscripts.second]);
                ObiektGrawitacyjny &obiektGrawitacyjny1 = obiektyGrawitacyjne[vectorSubscripts.first];
                ObiektGrawitacyjny &obiektGrawitacyjny2 = obiektyGrawitacyjne[vectorSubscripts.second];
                pair<double, double> cord1 = obiektGrawitacyjny1.getCord();
                pair<double, double> cord2 = obiektGrawitacyjny2.getCord();
                //cord1 -> cord2 vector
                pair<double, double> &versordC1C2 = versorMap[pair(cord1, cord2)];
                //cord2 -> cord1 vector
                pair<double, double> &versorC2C1 = versorMap[pair(cord2, cord1)];
                obiektGrawitacyjny1.setForce(force_, versordC1C2);
                obiektGrawitacyjny2.setForce(force_, versorC2C1);
            } while (std::next_permutation(boolRepresentationOfCombination.begin(),boolRepresentationOfCombination.end()));
            resetBoolRepresentationOfCombination();

//obliczanie delta vector predkosci i dodawanie ich do aktualnie posiadanych wektorow
//przesuwanie obiektow na podstawie wektora predkosci
        for (auto it = obiektyGrawitacyjne.begin(); it != obiektyGrawitacyjne.end(); it++)
        {
            //obliczanie predkosci
            double deltaVelocityHorizontal = it->returnForce().first * DELTA_TIME_PER_TICK_ / it->returnMass(),
                    deltaVelocityVertical = it->returnForce().second * DELTA_TIME_PER_TICK_ / it->returnMass();
            pair<double, double> deltaVelocityHorizontalVertical{deltaVelocityHorizontal, deltaVelocityVertical};
            it->increseVelocity(deltaVelocityHorizontalVertical);

            //obliczanie przemieszczen
            double deltaCordHorizontal = it->returnVelocity().first * DELTA_TIME_PER_TICK_;
            double deltaCordVertical = it->returnVelocity().second * DELTA_TIME_PER_TICK_;
            pair<double, double> deltaCordVector{deltaCordHorizontal, deltaCordVertical};
            it->increseCord(deltaCordVector);
        }
//scalanie obiektow bedacych odpowiednio blisko
        if (obiektyGrawitacyjne.size() > 1)
        {
            do {
                pair<int, int> vectorSubscripts = returnSubscriptsForPairInVector(boolRepresentationOfCombination);
                double distance = distanceBetween(obiektyGrawitacyjne[vectorSubscripts.first],
                                                  obiektyGrawitacyjne[vectorSubscripts.second]);
                if (distance <= MINIMAL_DISTANCE_TO_MERGE) {
                    ObiektGrawitacyjny ob1 = obiektyGrawitacyjne[vectorSubscripts.first];
                    ObiektGrawitacyjny ob2 = obiektyGrawitacyjne[vectorSubscripts.second];
                    double sumofmass = ob1.returnMass() + ob2.returnMass(),
                            coefficient1 = ob1.returnMass() / sumofmass,
                            coefficient2 = ob2.returnMass() / sumofmass;
                    pair<double, double> velocitySum{
                            ob1.returnVelocity().first * coefficient1 + ob2.returnVelocity().first * coefficient2,
                            ob1.returnVelocity().second * coefficient1 + ob2.returnVelocity().second * coefficient2};
                    obiektyGrawitacyjne.push_back(
                            ObiektGrawitacyjny{ob1.getCord().first, ob1.getCord().second, sumofmass,
                                               velocitySum});
                    obiektyGrawitacyjne.erase(obiektyGrawitacyjne.begin() + vectorSubscripts.first);
                    auto iteratorToSecondToDelete = std::find(obiektyGrawitacyjne.begin(), obiektyGrawitacyjne.end(),
                                                              ob2);
                    if (iteratorToSecondToDelete != obiektyGrawitacyjne.end())
                        obiektyGrawitacyjne.erase(iteratorToSecondToDelete);
                    boolRepresentationOfCombination.empty();
                    boolRepresentationOfCombination.resize(obiektyGrawitacyjne.size());
                    resetRepresentationOfCombination(boolRepresentationOfCombination);
                }
            } while (std::next_permutation(boolRepresentationOfCombination.begin(),
                                           boolRepresentationOfCombination.end()));
            resetRepresentationOfCombination(boolRepresentationOfCombination);
        }
    }
//usuwanie obiektow bedacych poza obszarem rysowania
//bardzo obciazajaca sekcjasjja
//!!!!!!!!!!!!!double free or corruption (out)
//w tym fragmencie kodu
//    if(obiektyGrawitacyjne.size()>0)
//    {
//        int n_oj_object_to_delete{0};
//        int granica_przesuniecia_obiektu_poza_ekran = 500;
//        for_each(obiektyGrawitacyjne.begin(), obiektyGrawitacyjne.end(), [&](ObiektGrawitacyjny ob) {
//            if (ob.getCord().first > m_window.GetWindowSize().x + granica_przesuniecia_obiektu_poza_ekran)
//                n_oj_object_to_delete++;
//            else if (ob.getCord().second > m_window.GetWindowSize().y + granica_przesuniecia_obiektu_poza_ekran)
//                n_oj_object_to_delete++;
//        });
//        for (int i = 0; i < n_oj_object_to_delete; i++)
//        {
//            for (auto it = obiektyGrawitacyjne.begin(); it != obiektyGrawitacyjne.end(); it++)
//            {
//                if (it->getCord().first > m_window.GetWindowSize().x + granica_przesuniecia_obiektu_poza_ekran ||
//                    it->getCord().second > m_window.GetWindowSize().y + granica_przesuniecia_obiektu_poza_ekran)
//                {
//                    {obiektyGrawitacyjne.erase(it);
//                    break;}
//                }
//            }
//        }
//        resetBoolRepresentationOfCombination();
//    }

}


void Game::Render(){
	m_window.BeginDraw(); // Clear.

    for(auto &obj:obiektyGrawitacyjne)
        m_window.Draw(obj);

    if(nowyObiektGrawitacyjny[0].second)
        m_window.Draw(nowyObiektGrawitacyjny[0].first);

    m_window.EndDraw(); // Display.
}






