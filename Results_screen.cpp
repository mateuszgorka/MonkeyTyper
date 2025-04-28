#include "Results_screen.h"
#include <iostream>

ResultsScreen::ResultsScreen(float width, float height) : finished(false) {
    if (!font.loadFromFile("assets/fonts/Roboto-Italic.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    resultText.setFont(font);
    resultText.setCharacterSize(40);
    resultText.setFillColor(sf::Color::White);
    resultText.setStyle(sf::Text::Bold);

    missedWordsText.setFont(font);
    missedWordsText.setCharacterSize(24);
    missedWordsText.setFillColor(sf::Color::Red);
    missedWordsText.setStyle(sf::Text::Bold);

    difficultyText.setFont(font);
    difficultyText.setCharacterSize(24);
    difficultyText.setFillColor(sf::Color::White);
    difficultyText.setStyle(sf::Text::Bold);

    setButtonStyle(backB, backBT, "Back to Menu", width / 2 - 100, height - 100);
}

void ResultsScreen::setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos) {
    float buttonWidth = 200;
    float buttonHeight = 60;

    button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(sf::Color(70, 130, 180, 150));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2);
    button.setPosition(sf::Vector2f(xPos, yPos));

    buttonText.setFont(font);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setPosition(xPos + (buttonWidth - buttonText.getGlobalBounds().width) / 2, yPos + (buttonHeight - buttonText.getGlobalBounds().height) / 2 - 10);
}

void ResultsScreen::show(sf::RenderWindow& window, int score, int missedWords, const std::string& difficulty) {
    resultText.setString("You scored: " + std::to_string(score) + " points.");
    resultText.setPosition((window.getSize().x - resultText.getLocalBounds().width) / 2, 100.f);

    missedWordsText.setString("Missed Words: " + std::to_string(missedWords));
    missedWordsText.setPosition((window.getSize().x - missedWordsText.getLocalBounds().width) / 2, resultText.getPosition().y + 50.f);

    difficultyText.setString("Difficulty: " + difficulty);
    difficultyText.setPosition((window.getSize().x - difficultyText.getLocalBounds().width) / 2, missedWordsText.getPosition().y + 50.f);

    finished = false;

    while (window.isOpen() && !finished) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    if (backB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {  // -> Vector2f 2 wymiarowe vectory  https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Vector2.php
                        finished = true;
                    }
                }
            }
        }

        window.clear();
        window.draw(resultText);
        window.draw(missedWordsText);
        window.draw(difficultyText);
        window.draw(backB);
        window.draw(backBT);
        window.display();
    }
}


