#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "PatientList.h"

class Menu {
private:
    sf::Font font;
    static const int NUM_OPTIONS = 6;
    sf::Text options[NUM_OPTIONS];
    int selectedIndex;

public:
    explicit Menu(const sf::Font& menuFont, sf::RenderWindow& window);  
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window, PatientList& patientList);
    void handleMouse(sf::Vector2i mousePos, sf::RenderWindow& window, PatientList& patientList);  // Mouse handling
};

#endif
