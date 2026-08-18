#include "DeleteRecord.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void DeleteRecord::execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/background.jpg")) return;
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Text title("Delete Patient Record", font, 36);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);
    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 50);

    if (patientList.isEmpty()) {
        sf::Text noRecordsPrompt("Record is Empty...!", font, 24);
        noRecordsPrompt.setFillColor(sf::Color::White);
        noRecordsPrompt.setOutlineColor(sf::Color::Black);
        noRecordsPrompt.setOutlineThickness(1);
        noRecordsPrompt.setPosition(window.getSize().x / 2 - noRecordsPrompt.getLocalBounds().width / 2, 120);

        sf::Text promptMessage("Press Escape to Return to Main Menu", font, 20);
        promptMessage.setFillColor(sf::Color::White);
        promptMessage.setOutlineColor(sf::Color::Black);
        promptMessage.setOutlineThickness(1);
        promptMessage.setPosition(window.getSize().x / 2 - promptMessage.getLocalBounds().width / 2, 170);

        // Dynamic box for text
        float padding = 20.0f;
        sf::FloatRect textBounds1 = noRecordsPrompt.getLocalBounds();
        sf::FloatRect textBounds2 = promptMessage.getLocalBounds();
        float boxWidth = std::max(textBounds1.width, textBounds2.width) + padding * 2;
        float boxHeight = textBounds1.height + textBounds2.height + padding * 3;

        // Create a rectangle for the prompt box
        sf::RectangleShape displayBox(sf::Vector2f(boxWidth, boxHeight));
        displayBox.setFillColor(sf::Color(50, 50, 50, 180));
        displayBox.setOutlineColor(sf::Color::White);
        displayBox.setOutlineThickness(2);
        displayBox.setPosition(
            (window.getSize().x - boxWidth) / 2,  // Center horizontally
            (window.getSize().y - boxHeight) / 2 // Center vertically
        );

        // Position texts inside the box
        noRecordsPrompt.setPosition(displayBox.getPosition().x + padding, displayBox.getPosition().y + padding);
        promptMessage.setPosition(displayBox.getPosition().x + padding, noRecordsPrompt.getPosition().y + textBounds1.height + padding);

        bool isRunning = true;
        while (isRunning && window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        isRunning = false;
                    }
                }
            }

            window.clear();
            window.draw(backgroundSprite);
            window.draw(displayBox);
            window.draw(noRecordsPrompt);
            window.draw(promptMessage);
            window.display();
        }
        return;
    }

    sf::Text inputPrompt("Enter Serial Number to Delete:", font, 24);
    inputPrompt.setFillColor(sf::Color::White);
    inputPrompt.setOutlineColor(sf::Color::Black);
    inputPrompt.setOutlineThickness(1);
    inputPrompt.setPosition(window.getSize().x / 2 - inputPrompt.getLocalBounds().width / 2, 120);

    sf::RectangleShape inputBox;
    inputBox.setFillColor(sf::Color(50, 50, 50, 180));
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setSize(sf::Vector2f(600, 40));
    inputBox.setPosition(window.getSize().x / 2 - inputBox.getSize().x / 2, 155);

    sf::Text serialInput("", font, 24);
    serialInput.setFillColor(sf::Color::White);
    serialInput.setOutlineColor(sf::Color::Black);
    serialInput.setOutlineThickness(1);
    serialInput.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 5);

    sf::Text resultMessage("", font, 24);
    resultMessage.setFillColor(sf::Color::White);
    resultMessage.setOutlineColor(sf::Color::Black);
    resultMessage.setOutlineThickness(1);
    resultMessage.setPosition(window.getSize().x / 2 - resultMessage.getLocalBounds().width / 2, 250);

    std::string serialBuffer;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !serialBuffer.empty()) {
                    serialBuffer.pop_back();
                } else if (event.text.unicode == '\r') {
                    try {
                        int serial = std::stoi(serialBuffer);
                        if (patientList.deletePatient(serial)) {
                            resultMessage.setString("Record deleted successfully.");
                        } else {
                            resultMessage.setString("Record not found.");
                        }
                        serialBuffer.clear();
                    } catch (std::exception&) {
                        resultMessage.setString("Invalid input.");
                    }
                } else if (event.text.unicode < 128) {
                    serialBuffer += static_cast<char>(event.text.unicode);
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }
            }
        }

        serialInput.setString("Serial: " + serialBuffer);

        // Dynamic box for result message
        float padding = 20.0f;
        sf::FloatRect resultBounds = resultMessage.getLocalBounds();
        float resultBoxWidth = resultBounds.width + padding * 2;
        float resultBoxHeight = resultBounds.height + padding * 2;

        sf::RectangleShape resultBox(sf::Vector2f(resultBoxWidth, resultBoxHeight));
        resultBox.setFillColor(sf::Color(50, 50, 50, 180));
        resultBox.setOutlineColor(sf::Color::White);
        resultBox.setOutlineThickness(2);
        resultBox.setPosition(window.getSize().x / 2 - resultBoxWidth / 2, 250);

        resultMessage.setPosition(resultBox.getPosition().x + padding, resultBox.getPosition().y + padding);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(inputPrompt);
        window.draw(inputBox);
        window.draw(serialInput);
        window.draw(resultBox);
        window.draw(resultMessage);
        window.display();
    }
}