#include "AddRecord.h"
#include <iostream>

void AddRecord::execute(sf::RenderWindow &window, sf::Font &font, PatientList &patientList)
{
    // Setup background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/background.jpg"))
        return;
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    // Title
    sf::Text title("Add New Patient Record", font, 36);
    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);

    // Fields and input logic
    sf::Text inputs[6];
    std::string inputLabels[6] = {
        "Enter Patient Name",
        "Enter Patient Father Name",
        "Enter Patient Birth Year",
        "Enter Ward Assigned",
        "Enter Patient ID",
        "Enter Days of Stay"};
    std::string inputValues[6] = {"", "", "", "", "", ""};
    sf::RectangleShape fields[6];
    int currentField = -1;
    bool isEntering = true;

    // Initialize fields and input labels
    float fieldWidth = 700.0f;
    float fieldHeight = 40.0f;
    float padding = 15.0f;
    float verticalSpacing = 30.0f;

    for (int i = 0; i < 6; i++)
    {
        inputs[i].setFont(font);
        inputs[i].setString(inputLabels[i] + ": " + inputValues[i]);
        inputs[i].setCharacterSize(28);
        inputs[i].setFillColor(sf::Color::White);
        inputs[i].setOutlineColor(sf::Color::Black);
        inputs[i].setOutlineThickness(1);
        inputs[i].setPosition(window.getSize().x / 2 - fieldWidth / 2 + padding, 150 + i * (fieldHeight + verticalSpacing));

        fields[i].setPosition(window.getSize().x / 2 - fieldWidth / 2, 150 + i * (fieldHeight + verticalSpacing) - 5);
        fields[i].setSize(sf::Vector2f(fieldWidth, fieldHeight));
        fields[i].setFillColor(sf::Color(50, 50, 50, 180));
        fields[i].setOutlineColor(i == currentField ? sf::Color::Yellow : sf::Color::White);
        fields[i].setOutlineThickness(2);
    }

    // Create Enter Button
    sf::RectangleShape enterButton;
    enterButton.setSize(sf::Vector2f(300, 50));
    enterButton.setFillColor(sf::Color(50, 50, 50, 180));
    enterButton.setOutlineColor(sf::Color::White);
    enterButton.setOutlineThickness(2);
    float enterButtonY = 150 + 6 * (fieldHeight + verticalSpacing) + verticalSpacing;
    enterButton.setPosition(window.getSize().x / 2 - enterButton.getSize().x / 2, enterButtonY);

    sf::Text enterText("Enter", font, 28);
    enterText.setFillColor(sf::Color::White);
    enterText.setOutlineColor(sf::Color::Black);
    enterText.setOutlineThickness(1);
    enterText.setPosition(
        enterButton.getPosition().x + enterButton.getSize().x / 2 - enterText.getLocalBounds().width / 2,
        enterButton.getPosition().y + enterButton.getSize().y / 2 - enterText.getLocalBounds().height / 2 - enterText.getLocalBounds().top);

    // Error message
    sf::Text errorMessage("Error: Patient ID already existed", font, 28);
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setOutlineColor(sf::Color::Black);
    errorMessage.setOutlineThickness(1);
    errorMessage.setPosition(window.getSize().x / 2 - errorMessage.getLocalBounds().width / 2, enterButtonY + 60);
    bool showError = false;

    while (isEntering && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !inputValues[currentField].empty())
                {
                    inputValues[currentField].pop_back();
                }
                else if (event.text.unicode == '\r')
                {
                    currentField++;
                    if (currentField >= 6)
                    {
                        currentField = 0;
                    }
                }
                else if (event.text.unicode < 128 && inputValues[currentField].length() < 50)
                {
                    inputValues[currentField] += static_cast<char>(event.text.unicode);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < 6; i++)
                    {
                        if (fields[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            currentField = i;
                            break;
                        }
                    }
                    if (enterButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        if (patientList.isIdUnique(inputValues[4]))
                        {
                            isEntering = false;
                        }
                        else
                        {
                            showError = true;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 6; i++)
        {
            inputs[i].setString(inputLabels[i] + ": " + inputValues[i]);
            fields[i].setOutlineColor(i == currentField ? sf::Color::Yellow : sf::Color::White);
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        for (int i = 0; i < 6; i++)
        {
            window.draw(fields[i]);
            window.draw(inputs[i]);
        }
        window.draw(enterButton);
        window.draw(enterText);
        if (showError)
        {
            window.draw(errorMessage);
        }
        window.display();
    }

    if (!inputValues[0].empty() && !inputValues[4].empty() && !inputValues[5].empty())
    {
        patientList.addPatient(patientList.getAllPatients().size() + 1, inputValues[0], inputValues[1], inputValues[2],
                               inputValues[3], inputValues[4], std::stoi(inputValues[5]));
    }

    return;
}