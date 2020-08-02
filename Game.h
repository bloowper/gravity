#pragma once
#include "Window.h"
#include "ObiektGrawitacyjny.h"
#include "someMethods.h"
#include <map>

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();
private:
	void resetBoolRepresentationOfCombination();
    void setting_the_starting_position_of_the_objects();
    ObiektGrawitacyjny* locate_nearest_gravity_obj();
    double returnDistanceMouseObj(ObiektGrawitacyjny obj);

    Window m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;
    bool pause;
    bool graphic_velocity_vector;

    vector<ObiektGrawitacyjny> obiektyGrawitacyjne{};
    map<pair<pair<double,double>,pair<double,double>>,pair<double,double>> versorMap;
    vector<int> boolRepresentationOfCombination;//vector who contains combination of 2 element from vector<ObiektyGrawitacyjne> obiektyGrawitacyjne
    vector<pair<ObiektGrawitacyjny,bool>> nowyObiektGrawitacyjny{};// there was an error mwhen pair<bool,ObiektGrawitacyjny> idk why. so using vector with only one element

};