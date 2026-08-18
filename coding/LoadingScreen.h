#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <SFML/Graphics.hpp>

class LoadingScreen {
public:
    static void show(sf::RenderWindow& window, sf::Sprite& background, sf::Font& font, sf::Color barColor);
};

#endif