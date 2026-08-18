#include "DisplayRecord.h"
#include "AddRecord.h"
#include <sstream>  // For string conversion

void DisplayRecord::execute(sf::RenderWindow& window, sf::Font& font, PatientList& patientList) {
    // Load background texture and set scale
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/background.jpg")) return;
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    // Title text for the display
    sf::Text title("All Patient Records", font, 36);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);
    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 50);

    auto records = patientList.getAllPatients();
    std::vector<sf::RectangleShape> tableGrid;
    std::vector<sf::Text> tableTexts;

    // Column positions and sizes
    const int numCols = 7;
    const int col1X = 50;  // Starting X position for the first column
    const int rowHeight = 40;
    const int tableStartY = 120;
    const float colWidth = (window.getSize().x - col1X * 2) / numCols; // Dynamic column width

    if (records.empty()) {
        // No records message
        sf::Text noRecordsMessage("Please Add Record first....!", font, 24);
        noRecordsMessage.setFillColor(sf::Color::White);
        noRecordsMessage.setOutlineColor(sf::Color::Black);
        noRecordsMessage.setOutlineThickness(1);

        // Prompt to add record or return to menu
        sf::Text promptMessage("Press Enter to Add Record or Escape to Return to Main Menu", font, 20);
        promptMessage.setFillColor(sf::Color::White);
        promptMessage.setOutlineColor(sf::Color::Black);
        promptMessage.setOutlineThickness(1);

        // Dynamic box for text
        float padding = 20.0f;
        sf::FloatRect textBounds1 = noRecordsMessage.getLocalBounds();
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
        noRecordsMessage.setPosition(displayBox.getPosition().x + padding, displayBox.getPosition().y + padding);
        promptMessage.setPosition(displayBox.getPosition().x + padding, noRecordsMessage.getPosition().y + textBounds1.height + padding);

        tableTexts.push_back(noRecordsMessage);
        tableTexts.push_back(promptMessage);
        tableGrid.push_back(displayBox);
    } else {
        // Draw header row
        const std::string headers[] = {"Sr.No", "Name", "Father", "ID", "Birth Year", "Ward", "Days of Stay"};
        for (size_t i = 0, x = col1X; i < numCols; ++i) {
            sf::Text header(headers[i], font, 20);
            header.setPosition(x, tableStartY);
            header.setFillColor(sf::Color::White);
            header.setOutlineColor(sf::Color::Black);
            header.setOutlineThickness(1);
            tableTexts.push_back(header);
            x += colWidth;
        }

        // Render patient records
        for (size_t i = 0; i < records.size(); ++i) {
            float yPosition = tableStartY + rowHeight * (i + 1);
            sf::Color rowColor = (i % 2 == 0) ? sf::Color(50, 50, 50, 180) : sf::Color(80, 80, 80, 180);

            // Draw background for each row
            sf::RectangleShape rowBackground(sf::Vector2f(window.getSize().x - col1X * 2, rowHeight));
            rowBackground.setPosition(col1X, yPosition);
            rowBackground.setFillColor(rowColor);
            tableGrid.push_back(rowBackground);

            // Draw record data
            const std::string rowData[] = {
                std::to_string(records[i]->srNo), records[i]->name, records[i]->fname, records[i]->id,
                records[i]->dob, records[i]->ward, std::to_string(records[i]->days)};

            for (size_t j = 0, x = col1X; j < numCols; ++j) {
                sf::Text cellText(rowData[j], font, 18);
                cellText.setPosition(x + 5, yPosition + 5); // Padding inside cell
                cellText.setFillColor(sf::Color::White);
                cellText.setOutlineColor(sf::Color::Black);
                cellText.setOutlineThickness(1);
                tableTexts.push_back(cellText);

                // Draw cell border
                sf::RectangleShape cellBorder(sf::Vector2f(colWidth, rowHeight));
                cellBorder.setPosition(x, yPosition);
                cellBorder.setFillColor(sf::Color::Transparent);
                cellBorder.setOutlineColor(sf::Color::White);
                cellBorder.setOutlineThickness(1);
                tableGrid.push_back(cellBorder);

                x += colWidth;
            }
        }
    }

    // Event loop to handle input and window actions
    bool isRunning = true;
    while (isRunning && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (records.empty()) {
                        AddRecord::execute(window, font, patientList);
                        isRunning = false;  // Exit after adding record
                    }
                } else if (event.key.code == sf::Keyboard::Escape) {
                    isRunning = false;  // Exit on Escape key press
                }
            }
        }

        // Render everything to the window
        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        for (auto& row : tableGrid) {
            window.draw(row);
        }
        for (auto& text : tableTexts) {
            window.draw(text);
        }
        window.display();
    }
}