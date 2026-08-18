#include "LoginScreen.h"

bool LoginScreen::show(sf::RenderWindow& window, sf::Font& font, std::unordered_map<std::string, std::string>& users) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/background.jpg")) return false;
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Text title("Login", font, 36);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);
    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 50);

    sf::Text usernamePrompt("Username:", font, 24);
    usernamePrompt.setFillColor(sf::Color::White);
    usernamePrompt.setOutlineColor(sf::Color::Black);
    usernamePrompt.setOutlineThickness(1);
    usernamePrompt.setPosition(window.getSize().x / 2 - usernamePrompt.getLocalBounds().width / 2, 150);

    sf::Text passwordPrompt("Password:", font, 24);
    passwordPrompt.setFillColor(sf::Color::White);
    passwordPrompt.setOutlineColor(sf::Color::Black);
    passwordPrompt.setOutlineThickness(1);
    passwordPrompt.setPosition(window.getSize().x / 2 - passwordPrompt.getLocalBounds().width / 2, 250);

    sf::RectangleShape usernameBox;
    usernameBox.setFillColor(sf::Color(50, 50, 50, 180));
    usernameBox.setOutlineColor(sf::Color::White);
    usernameBox.setOutlineThickness(2);
    usernameBox.setSize(sf::Vector2f(400, 40));
    usernameBox.setPosition(window.getSize().x / 2 - usernameBox.getSize().x / 2, 185);

    sf::RectangleShape passwordBox;
    passwordBox.setFillColor(sf::Color(50, 50, 50, 180));
    passwordBox.setOutlineColor(sf::Color::White);
    passwordBox.setOutlineThickness(2);
    passwordBox.setSize(sf::Vector2f(400, 40));
    passwordBox.setPosition(window.getSize().x / 2 - passwordBox.getSize().x / 2, 285);

    sf::Text usernameInput("", font, 24);
    usernameInput.setFillColor(sf::Color::White);
    usernameInput.setOutlineColor(sf::Color::Black);
    usernameInput.setOutlineThickness(1);
    usernameInput.setPosition(usernameBox.getPosition().x + 10, usernameBox.getPosition().y + 5);

    sf::Text passwordInput("", font, 24);
    passwordInput.setFillColor(sf::Color::White);
    passwordInput.setOutlineColor(sf::Color::Black);
    passwordInput.setOutlineThickness(1);
    passwordInput.setPosition(passwordBox.getPosition().x + 10, passwordBox.getPosition().y + 5);

    sf::RectangleShape loginButton;
    loginButton.setFillColor(sf::Color(50, 50, 50, 180));
    loginButton.setOutlineColor(sf::Color::White);
    loginButton.setOutlineThickness(2);
    loginButton.setSize(sf::Vector2f(200, 50));
    loginButton.setPosition(window.getSize().x / 2 - loginButton.getSize().x / 2, 350);

    sf::Text loginButtonText("Login", font, 24);
    loginButtonText.setFillColor(sf::Color::White);
    loginButtonText.setOutlineColor(sf::Color::Black);
    loginButtonText.setOutlineThickness(1);
    loginButtonText.setPosition(loginButton.getPosition().x + loginButton.getSize().x / 2 - loginButtonText.getLocalBounds().width / 2, loginButton.getPosition().y + 10);

    std::string usernameBuffer;
    std::string passwordBuffer;
    bool isPassword = false;
    bool isUsernameSelected = false;
    bool isPasswordSelected = false;

    sf::Text loginMessage("", font, 24);
    loginMessage.setFillColor(sf::Color::Red);
    loginMessage.setOutlineColor(sf::Color::Black);
    loginMessage.setOutlineThickness(1);

    bool isRunning = true;
    while (isRunning && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (isPasswordSelected && !passwordBuffer.empty()) {
                        passwordBuffer.pop_back();
                    } else if (isUsernameSelected && !usernameBuffer.empty()) {
                        usernameBuffer.pop_back();
                    }
                } else if (event.text.unicode == '\r') {
                    if (isUsernameSelected) {
                        isUsernameSelected = false;
                        isPasswordSelected = true;
                    } else if (isPasswordSelected) {
                        if (users.find(usernameBuffer) != users.end() && users[usernameBuffer] == passwordBuffer) {
                            loginMessage.setString("Login successful!");
                            loginMessage.setPosition(window.getSize().x / 2 - loginMessage.getLocalBounds().width / 2, 420);
                            isRunning = false;
                        } else {
                            loginMessage.setString("Invalid username or password.");
                            loginMessage.setPosition(window.getSize().x / 2 - loginMessage.getLocalBounds().width / 2, 420);
                        }
                    }
                } else if (event.text.unicode < 128) {
                    if (isPasswordSelected) {
                        passwordBuffer += static_cast<char>(event.text.unicode);
                    } else if (isUsernameSelected) {
                        usernameBuffer += static_cast<char>(event.text.unicode);
                    }
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (usernameBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        isUsernameSelected = true;
                        isPasswordSelected = false;
                    } else if (passwordBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        isUsernameSelected = false;
                        isPasswordSelected = true;
                    } else if (loginButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (users.find(usernameBuffer) != users.end() && users[usernameBuffer] == passwordBuffer) {
                            loginMessage.setString("Login successful!");
                            loginMessage.setPosition(window.getSize().x / 2 - loginMessage.getLocalBounds().width / 2, 420);
                            isRunning = false;
                        } else {
                            loginMessage.setString("Invalid username or password.");
                            loginMessage.setPosition(window.getSize().x / 2 - loginMessage.getLocalBounds().width / 2, 420);
                        }
                    }
                }
            }
        }

        usernameInput.setString(usernameBuffer);
        passwordInput.setString(std::string(passwordBuffer.size(), '*'));

        // Change the color of the selected box
        if (isUsernameSelected) {
            usernameBox.setFillColor(sf::Color(70, 70, 70, 180));
            passwordBox.setFillColor(sf::Color(50, 50, 50, 180));
        } else if (isPasswordSelected) {
            passwordBox.setFillColor(sf::Color(70, 70, 70, 180));
            usernameBox.setFillColor(sf::Color(50, 50, 50, 180));
        } else {
            usernameBox.setFillColor(sf::Color(50, 50, 50, 180));
            passwordBox.setFillColor(sf::Color(50, 50, 50, 180));
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(usernamePrompt);
        window.draw(usernameBox);
        window.draw(usernameInput);
        window.draw(passwordPrompt);
        window.draw(passwordBox);
        window.draw(passwordInput);
        window.draw(loginButton);
        window.draw(loginButtonText);
        window.draw(loginMessage);
        window.display();
    }

    return !isRunning;
}