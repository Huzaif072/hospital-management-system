#include "LoadingScreen.h"
#include <iostream>

void LoadingScreen::show(sf::RenderWindow &window, sf::Sprite &background, sf::Font &font, sf::Color barColor) {
    sf::Text loadingText("Loading...", font, 40);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setOutlineColor(sf::Color::Black);
    loadingText.setOutlineThickness(3);
    loadingText.setPosition(
        window.getSize().x / 2.0f - loadingText.getGlobalBounds().width / 2.0f,
        window.getSize().y / 2.0f - 100);

    sf::RectangleShape progressBarOutline(sf::Vector2f(600, 30));
    progressBarOutline.setOutlineThickness(2);
    progressBarOutline.setOutlineColor(sf::Color::White);
    progressBarOutline.setPosition(
        window.getSize().x / 2.0f - progressBarOutline.getSize().x / 2.0f,
        window.getSize().y / 2.0f);

    sf::RectangleShape progressBar(sf::Vector2f(0, 30));
    progressBar.setFillColor(barColor);
    progressBar.setPosition(progressBarOutline.getPosition());

    sf::Clock clock;
    const float maxProgress = 600;
    float progress = 0.0f;

    while (progress < maxProgress) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        progress = clock.getElapsedTime().asSeconds() * 200;
        if (progress > maxProgress)
            progress = maxProgress;
        progressBar.setSize(sf::Vector2f(progress, 30));

        window.clear();
        window.draw(background);
        window.draw(loadingText);
        window.draw(progressBarOutline);
        window.draw(progressBar);
        window.display();
    }
}