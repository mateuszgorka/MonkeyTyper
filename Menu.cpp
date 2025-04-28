#include "Menu.h"
#include <iostream>

    Menu::Menu(float width, float height) {


    font.loadFromFile("assets/fonts/Roboto-Italic.ttf");
    logo.setFont(font);
    logo.setFillColor(sf::Color::White);
    logo.setString("Formula Typer");
    logo.setCharacterSize(60);
    logo.setPosition(width / 2 - logo.getGlobalBounds().width / 2, height / 8);


    positionButtons(width, height);
}

void Menu::positionButtons(float width, float height) {
    float buttonWidth = 300;
    float xPos = width / 2 - buttonWidth / 2;
    float yPos = height / 2 - 100;

    setButtonStyle(startB, startBT, "Start", xPos, yPos);
    setButtonStyle(optionsB, optionsBT, "Options", xPos, yPos + 80);
    setButtonStyle(exitB, exitBT, "Exit", xPos, yPos + 160);

}

void Menu::setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos) {
    float buttonWidth = 300;
    float buttonHeight = 60;

    button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(sf::Color(70, 130, 180, 150));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2);
    button.setPosition(sf::Vector2f(xPos, yPos));

    buttonText.setFont(font);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setPosition(xPos + (buttonWidth - buttonText.getGlobalBounds().width) / 2, yPos + (buttonHeight - buttonText.getGlobalBounds().height) / 2 - 10);
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(logo);
    window.draw(startB);
    window.draw(optionsB);
    window.draw(exitB);
    window.draw(startBT);
    window.draw(optionsBT);
    window.draw(exitBT);
}



