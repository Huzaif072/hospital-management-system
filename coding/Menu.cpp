#include "Menu.h"
#include "AddRecord.h"
#include "EditRecord.h"
#include "SearchRecord.h"
#include "DeleteRecord.h"
#include "DisplayRecord.h"

Menu::Menu(const sf::Font& menuFont, sf::RenderWindow& window) : font(menuFont), selectedIndex(0) {
    std::string labels[6] = {"Add Record", "Edit Record", "Search Record", "Delete Record", "Display Record", "Quit Program"};
    
    // Calculate the starting position to center the menu
    float startX = 225.f;
    float totalMenuHeight = 6 * 60; // 6 options, each 60 pixels tall
    float startY = (window.getSize().y - totalMenuHeight) / 2.0f;

    for (int i = 0; i < 6; i++) {
        options[i].setFont(font);
        options[i].setString(labels[i]);
        options[i].setCharacterSize(35);
        options[i].setPosition(startX, startY + i * 60);
        options[i].setFillColor(i == 0 ? sf::Color(93, 138, 168) : sf::Color::White);
        options[i].setOutlineColor(sf::Color::Black);
        options[i].setOutlineThickness(2);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    // Draw the menu options centered on the screen
    for (auto& option : options) {
        window.draw(option);
    }
}

void Menu::handleEvent(sf::Event& event, sf::RenderWindow& window, PatientList& patientList) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            options[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex = (selectedIndex - 1 + 6) % 6;
            options[selectedIndex].setFillColor(sf::Color(93, 138, 168));
        } else if (event.key.code == sf::Keyboard::Down) {
            options[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex = (selectedIndex + 1) % 6;
            options[selectedIndex].setFillColor(sf::Color(93, 138, 168));
        } else if (event.key.code == sf::Keyboard::Enter) {
            switch (selectedIndex) {
                case 0: AddRecord::execute(window, font, patientList); break;
                case 1: EditRecord::execute(window, font, patientList); break;
                case 2: SearchRecord::execute(window, font, patientList); break;
                case 3: DeleteRecord::execute(window, font, patientList); break;
                case 4: DisplayRecord::execute(window, font, patientList); break;
                case 5: window.close(); break;
            }
        }
    }
}

void Menu::handleMouse(sf::Vector2i mousePos, sf::RenderWindow& window, PatientList& patientList) {
    for (int i = 0; i < NUM_OPTIONS; ++i) {
        sf::FloatRect bounds = options[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            options[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex = i;
            options[selectedIndex].setFillColor(sf::Color(93, 138, 168));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                switch (selectedIndex) {
                    case 0: AddRecord::execute(window, font, patientList); break;
                    case 1: EditRecord::execute(window, font, patientList); break;
                    case 2: SearchRecord::execute(window, font, patientList); break;
                    case 3: DeleteRecord::execute(window, font, patientList); break;
                    case 4: DisplayRecord::execute(window, font, patientList); break;
                    case 5: window.close(); break;
                }
            }
        }
    }
}
