#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class LoginScreen {
public:
    static bool show(sf::RenderWindow& window, sf::Font& font, std::unordered_map<std::string, std::string>& users);
};

#endif // LOGINSCREEN_H