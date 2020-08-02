#include "Window.h"
#include <iostream>
Window::Window(){ Setup("Window", sf::Vector2u(640,480)); }
Window::Window(const std::string& title, const sf::Vector2u& size){ Setup(title,size); }
Window::~Window(){ Destroy(); }

void Window::Setup(const std::string title, const sf::Vector2u& size){
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	m_window.setFramerateLimit(240);

	Create();
}

void Window::Create(){
	auto style = (m_isFullscreen ? sf::Style::Fullscreen 
		: sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, style);
}

void Window::Destroy(){
	m_window.close();
}

void Window::BeginDraw(){ m_window.clear(sf::Color::Black); }
void Window::EndDraw(){ m_window.display(); }

bool Window::IsDone(){ return m_isDone; }
bool Window::IsFullscreen(){ return m_isFullscreen; }

void Window::Draw(sf::Drawable& l_drawable){
	m_window.draw(l_drawable);
}

sf::Vector2u Window::GetWindowSize(){ return m_windowSize; }

void Window::ToggleFullscreen(){
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::Update() {
    sf::Event event;
    //POTRZEBNE PRZEPISANIE OD NOWA NA CZYSTO
    //POPRAWIC!
    while (m_window.pollEvent(event)) {
        //exit control
        if (event.type == sf::Event::Closed) { m_isDone = true; }
        //////
        //keyboard P
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) {
            EventUnit.keyboard_P_button.first = 1;
        }
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::P)) {
            EventUnit.keyboard_P_button.second = 1;
        }
        //////
        //keyboard D
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)) {
        EventUnit.keyboard_D_button.first = 1;
        }
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::D)) {
            EventUnit.keyboard_D_button.second = 1;
        }
        //////
        //keyboard up arrow
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
            EventUnit.keyboard_up.first = 1;
        }
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Up)) {
            EventUnit.keyboard_up.second = 1;
        }
        /////
        //keyboard down arrow
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
        EventUnit.keyboard_down.first = 1;
        }
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Down)) {
            EventUnit.keyboard_down.second = 1;
        }
        //////
        //keyboard left arrow
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
        EventUnit.keyboard_left.first = 1;
        }
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Left)) {
            EventUnit.keyboard_left.second = 1;
        }
        //////
        //keyboard rigth arrow
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
        EventUnit.keyboard_right.first = 1;
        }
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Right)) {
            EventUnit.keyboard_right.second = 1;
        }
        //////
        //mose L button
        if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
            EventUnit.mouseLbutton.first = true;
            EventUnit.isMouseLbutton = true;
        }
        if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) {
            EventUnit.mouseLbutton.second = true;
            EventUnit.isMouseLbutton = false;
        }
        //////
        //mouse R button
        if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Right)) {
            EventUnit.mouseRbutton.first = true;
            EventUnit.isMouseRbutton = true;
        }
        if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Right)) {
            EventUnit.mouseRbutton.second = true;
            EventUnit.isMouseRbutton = false;
        }
        //////
        //wheel
        if((event.type == sf::Event::MouseWheelMoved))
        {
            EventUnit.mouseWheel = event.mouseWheel.delta;
        }

    }

    //mouse position update
    EventUnit.mouseCord = {sf::Mouse::getPosition(m_window).x,sf::Mouse::getPosition(m_window).y};

}

eventUnit& Window::getEventUnit()
{
    return EventUnit;
}

void Window::resetEventUnit()
{
    //mouse left button
    EventUnit.mouseLbutton = {0,0};
    EventUnit.isMouseLbutton=0;
    //mouse right button
    EventUnit.mouseRbutton={0,0};
    EventUnit.isMouseRbutton=0;
    //keyboard P button
    EventUnit.keyboard_P_button={0, 0};
}
