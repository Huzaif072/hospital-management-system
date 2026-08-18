#include "EditRecord.h"
#include "AddRecord.h"
#include <sstream>

void EditRecord::execute(sf::RenderWindow &window, sf::Font &font, PatientList &patientList)
{
    if (patientList.isEmpty())
    {
        // Display a prompt if there are no records
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("img/background.jpg"))
            return;
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

        // No records message
        sf::Text noRecordsPrompt("No records found. Please Add a Record First.", font, 24);
        noRecordsPrompt.setFillColor(sf::Color::White);
        noRecordsPrompt.setOutlineColor(sf::Color::Black);
        noRecordsPrompt.setOutlineThickness(1);

        sf::Text promptMessage("Press Enter to Add Record or Escape to Return to Main Menu", font, 20);
        promptMessage.setFillColor(sf::Color::White);
        promptMessage.setOutlineColor(sf::Color::Black);
        promptMessage.setOutlineThickness(1);

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
            (window.getSize().x - boxWidth) / 2, // Center horizontally
            (window.getSize().y - boxHeight) / 2 // Center vertically
        );

        // Position texts inside the box
        noRecordsPrompt.setPosition(displayBox.getPosition().x + padding, displayBox.getPosition().y + padding);
        promptMessage.setPosition(displayBox.getPosition().x + padding, noRecordsPrompt.getPosition().y + textBounds1.height + padding);

        bool isRunning = true;
        while (isRunning && window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        AddRecord::execute(window, font, patientList);
                        isRunning = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
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

    // Load background and UI elements
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/background.jpg"))
        return;
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    sf::Text title("Edit Patient Record", font, 36);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);
    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 50); // Centered title

    sf::Text inputPrompt("Enter Serial Number of Patient to Edit:", font, 24);
    inputPrompt.setFillColor(sf::Color::White);
    inputPrompt.setOutlineColor(sf::Color::Black);
    inputPrompt.setOutlineThickness(1);
    inputPrompt.setPosition(window.getSize().x / 2 - inputPrompt.getLocalBounds().width / 2, 120); // Centered prompt

    sf::RectangleShape inputBox;
    inputBox.setFillColor(sf::Color(50, 50, 50, 180));
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setSize(sf::Vector2f(600, 40)); // Set width dynamically for input box
    inputBox.setPosition(window.getSize().x / 2 - inputBox.getSize().x / 2, 155);

    sf::Text serialInput("", font, 24);
    serialInput.setFillColor(sf::Color::White);
    serialInput.setOutlineColor(sf::Color::Black);
    serialInput.setOutlineThickness(1);
    serialInput.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 5); // Positioned inside input box

    std::string serialBuffer;
    Node *target = nullptr;

    // Input serial number of the patient
    while (window.isOpen() && !target)
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
                if (event.text.unicode == '\b' && !serialBuffer.empty())
                {
                    serialBuffer.pop_back(); // Handle backspace
                }
                else if (event.text.unicode == '\r')
                {
                    if (!serialBuffer.empty())
                    {
                        int serial = std::stoi(serialBuffer);
                        target = patientList.searchPatient(serial);
                        if (!target)
                        {
                            // Display "Record Not Found" prompt
                            sf::Text recordNotFoundPrompt("Record not found. Try Again.", font, 30);
                            recordNotFoundPrompt.setFillColor(sf::Color::White);
                            recordNotFoundPrompt.setOutlineColor(sf::Color::Black);
                            recordNotFoundPrompt.setOutlineThickness(1);

                            sf::Text promptMessage("Press Enter to Retry or Escape to Return to Main Menu", font, 24);
                            promptMessage.setFillColor(sf::Color::White);
                            promptMessage.setOutlineColor(sf::Color::Black);
                            promptMessage.setOutlineThickness(1);

                            // Calculate the width and height of the box
                            float padding = 10.0f;
                            float boxWidth = std::max(recordNotFoundPrompt.getLocalBounds().width, promptMessage.getLocalBounds().width) + 2 * padding;
                            float boxHeight = recordNotFoundPrompt.getLocalBounds().height + promptMessage.getLocalBounds().height + 3 * padding;

                            // Set positions for the text
                            recordNotFoundPrompt.setPosition(window.getSize().x / 2 - recordNotFoundPrompt.getLocalBounds().width / 2, window.getSize().y / 2 - boxHeight / 2 + padding);
                            promptMessage.setPosition(window.getSize().x / 2 - promptMessage.getLocalBounds().width / 2, window.getSize().y / 2 - boxHeight / 2 + recordNotFoundPrompt.getLocalBounds().height + 2 * padding);

                            // Create a box around the text
                            sf::RectangleShape box;
                            box.setSize(sf::Vector2f(boxWidth, boxHeight));
                            box.setFillColor(sf::Color(50, 50, 50, 180));
                            box.setOutlineColor(sf::Color::White);
                            box.setOutlineThickness(2);
                            box.setPosition(window.getSize().x / 2 - boxWidth / 2, window.getSize().y / 2 - boxHeight / 2);

                            bool isRunning = true;
                            while (isRunning && window.isOpen())
                            {
                                sf::Event event;
                                while (window.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed)
                                    {
                                        window.close();
                                    }
                                    else if (event.type == sf::Event::KeyPressed)
                                    {
                                        if (event.key.code == sf::Keyboard::Enter)
                                        {
                                            isRunning = false; // Allow retry
                                        }
                                        else if (event.key.code == sf::Keyboard::Escape)
                                        {
                                            return; // Exit to main menu
                                        }
                                    }
                                }

                                window.clear();
                                window.draw(backgroundSprite);
                                window.draw(box);
                                window.draw(recordNotFoundPrompt);
                                window.draw(promptMessage);
                                window.display();
                            }
                            serialBuffer.clear(); // Clear input for retry
                        }
                    }
                }
                else if (event.text.unicode < 128)
                {
                    serialBuffer += static_cast<char>(event.text.unicode);
                }
            }
        }

        serialInput.setString("Serial: " + serialBuffer);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(inputPrompt);
        window.draw(inputBox);
        window.draw(serialInput);
        window.display();
    }

    if (target)
    {
        // Fields for editing patient information
        std::string fieldLabels[] = {
            "Name", "Father's Name", "Date of Birth", "Ward", "Patient ID", "Days of Stay"};
        std::string fieldValues[] = {
            target->name, target->fname, target->dob, target->ward, target->id, std::to_string(target->days)};

        sf::Text fieldTexts[6];
        sf::RectangleShape fieldBoxes[6];
        int selectedField = -1;

        for (int i = 0; i < 6; i++)
        {
            fieldTexts[i].setFont(font);
            fieldTexts[i].setString(fieldLabels[i] + ": " + fieldValues[i]);
            fieldTexts[i].setCharacterSize(28);                                                                         // Increased text size
            fieldTexts[i].setPosition(window.getSize().x / 2 - fieldTexts[i].getLocalBounds().width / 2, 150 + i * 70); // Centered position
            fieldTexts[i].setFillColor(sf::Color::White);
            fieldTexts[i].setOutlineColor(sf::Color::Black);
            fieldTexts[i].setOutlineThickness(1);

            fieldBoxes[i].setPosition(window.getSize().x / 2 - 350, 150 + i * 70 - 5); // Centered position
            fieldBoxes[i].setSize(sf::Vector2f(700, 40));                              // Increased size of input boxes
            fieldBoxes[i].setFillColor(sf::Color(50, 50, 50, 180));
            fieldBoxes[i].setOutlineColor(i == selectedField ? sf::Color::Yellow : sf::Color::White);
            fieldBoxes[i].setOutlineThickness(2);
        }

        // Create Enter Button
        sf::RectangleShape enterButton;
        enterButton.setPosition(window.getSize().x / 2 - 150, 600); // Centered position
        enterButton.setSize(sf::Vector2f(300, 50));                 // Adjusted size
        enterButton.setFillColor(sf::Color(50, 50, 50, 180));
        enterButton.setOutlineColor(sf::Color::White);
        enterButton.setOutlineThickness(2);

        sf::Text enterText("Enter", font, 24);                                                     // Increased text size
        enterText.setPosition(window.getSize().x / 2 - enterText.getLocalBounds().width / 2, 610); // Centered text
        enterText.setFillColor(sf::Color::White);
        enterText.setOutlineColor(sf::Color::Black);
        enterText.setOutlineThickness(1);

        // Error message
        sf::Text errorMessage("Error: Patient ID already existed", font, 28);
        errorMessage.setFillColor(sf::Color::Red);
        errorMessage.setOutlineColor(sf::Color::Black);
        errorMessage.setOutlineThickness(1);
        errorMessage.setPosition(window.getSize().x / 2 - errorMessage.getLocalBounds().width / 2, 670);
        bool showError = false;

        bool isEditing = true;
        while (isEditing && window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < 6; i++)
                    {
                        if (fieldBoxes[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            selectedField = i;
                        }
                    }

                    // Handle Enter button click
                    if (enterButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        if (patientList.isIdUnique(fieldValues[4]) || fieldValues[4] == target->id)
                        {
                            // Submit the data
                            target->name = fieldValues[0];
                            target->fname = fieldValues[1];
                            target->dob = fieldValues[2];
                            target->ward = fieldValues[3];
                            target->id = fieldValues[4];
                            target->days = std::stoi(fieldValues[5]);
                            isEditing = false;
                        }
                        else
                        {
                            showError = true;
                        }
                    }
                }
                else if (event.type == sf::Event::TextEntered && selectedField != -1)
                {
                    if (event.text.unicode == '\b' && !fieldValues[selectedField].empty())
                    {
                        fieldValues[selectedField].pop_back();
                    }
                    else if (event.text.unicode == '\r')
                    {
                        if (patientList.isIdUnique(fieldValues[4]) || fieldValues[4] == target->id)
                        {
                            // Submit the data
                            target->name = fieldValues[0];
                            target->fname = fieldValues[1];
                            target->dob = fieldValues[2];
                            target->ward = fieldValues[3];
                            target->id = fieldValues[4];
                            target->days = std::stoi(fieldValues[5]);
                            isEditing = false;
                        }
                        else
                        {
                            showError = true;
                        }
                    }
                    else if (event.text.unicode < 128)
                    {
                        fieldValues[selectedField] += static_cast<char>(event.text.unicode);
                    }
                }
            }

            for (int i = 0; i < 6; i++)
            {
                fieldTexts[i].setString(fieldLabels[i] + ": " + fieldValues[i]);
                fieldBoxes[i].setOutlineColor(i == selectedField ? sf::Color::Yellow : sf::Color::White);
            }

            window.clear();
            window.draw(backgroundSprite);
            window.draw(title);
            window.draw(enterButton);
            window.draw(enterText);

            for (int i = 0; i < 6; i++)
            {
                window.draw(fieldBoxes[i]);
                window.draw(fieldTexts[i]);
            }

            if (showError) {
                window.draw(errorMessage);
            }

            window.display();
        }
    }
}
