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
	Window m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;

    vector<ObiektGrawitacyjny> obiektyGrawitacyjne{};
    map<pair<pair<double,double>,pair<double,double>>,pair<double,double>> versorMap;
    vector<int> boolRepresentationOfCombination;


};