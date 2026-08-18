#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "PatientList.h"
#include "LoadingScreen.h"
#include "AddRecord.h"
#include "EditRecord.h"
#include "SearchRecord.h"
#include "DeleteRecord.h"
#include "DisplayRecord.h"
#include "LoginScreen.h"
#include <iostream>
#include <unordered_map>

int main()
{
    // Create a full-screen window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Hospital Management System", sf::Style::Fullscreen);

    sf::Font font;
    if (!font.loadFromFile("font/Poppins-Regular.ttf"))
    {
        std::cerr << "Error: Failed to load font" << std::endl;
        return -1;
    }

    // Load a background texture for the menu
    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("img/background.jpg"))
    {
        std::cerr << "Error: Failed to load menu background image" << std::endl;
        return -1;
    }
    menuBackgroundTexture.setSmooth(true);
    sf::Sprite menuBackgroundSprite(menuBackgroundTexture);
    menuBackgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / menuBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / menuBackgroundTexture.getSize().y);

    // Load a separate background texture for the loading screen
    sf::Texture loadingBackgroundTexture;
    if (!loadingBackgroundTexture.loadFromFile("img/Loading_Screen.jpg"))
    { // Use your loading screen background image
        std::cerr << "Error: Failed to load loading screen background image" << std::endl;
        return -1;
    }
    loadingBackgroundTexture.setSmooth(true);
    sf::Sprite loadingBackgroundSprite(loadingBackgroundTexture);
    loadingBackgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / loadingBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / loadingBackgroundTexture.getSize().y);

    // Force window clearing at the start
    window.clear(sf::Color::Black);
    window.display();

    // Show loading screen with a custom loading background
    LoadingScreen::show(window, loadingBackgroundSprite, font, sf::Color::Black); // Use your custom loading background

    // Initialize user credentials
    std::unordered_map<std::string, std::string> users = {
        {"faraz", "faraz1234"},
        {"huzaif", "huzaif1234"},
        {"talal", "talal1234"},
        {"admin", "admin1234"}
    };

    // Show login screen
    if (!LoginScreen::show(window, font, users)) {
        return 0; // Exit if login fails or window is closed
    }

    // Initialize patient list and menu, pass the window reference to the menu constructor
    PatientList patientList;
    Menu menu(font, window); // Pass the window to Menu constructor

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            menu.handleEvent(event, window, patientList);
            if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed)
            {
                menu.handleMouse(sf::Mouse::getPosition(window), window, patientList);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(menuBackgroundSprite); // Draw shared menu background
        menu.draw(window);                 // Draw menu
        window.display();
    }

    return 0;
}