#include "options.h"
#include <iostream>

Options::Options(float width, float height) : selectedIndex(0), selectedFont(&font1) {




    font.loadFromFile("assets/fonts/Roboto-Italic.ttf");  // -> domyslna
    font1.loadFromFile("assets/fonts/Roboto-Italic.ttf");
    font2.loadFromFile("assets/fonts/RobotoMono-Italic-VariableFont_wght.ttf");
    font3.loadFromFile("assets/fonts/Tiny5-Regular.ttf");



    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setString("Options");
    title.setCharacterSize(40);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 14 - 20);

    difficultyTitle.setFont(font);
    difficultyTitle.setFillColor(sf::Color::White);
    difficultyTitle.setString("Difficulty:");
    difficultyTitle.setCharacterSize(30);
    difficultyTitle.setPosition(width / 2 - difficultyTitle.getGlobalBounds().width / 2, height / 6.5);

    fontTitle.setFont(font);
    fontTitle.setFillColor(sf::Color::White);
    fontTitle.setString("Font:");
    fontTitle.setCharacterSize(30);
    fontTitle.setPosition(width / 2 - fontTitle.getGlobalBounds().width / 2, height / 2.5);

    fontSizeTitle.setFont(font);
    fontSizeTitle.setFillColor(sf::Color::White);
    fontSizeTitle.setString("Font Size:");
    fontSizeTitle.setCharacterSize(30);
    fontSizeTitle.setPosition(width / 2 - fontSizeTitle.getGlobalBounds().width / 2, height / 2 + 80);



    positionButtons(width, height);
}

void Options::positionButtons(float width, float height) {
    float buttonWidth = 200;
    float buttonHeight = 60;
    float buttonSpacing = 20;
    float xPos = width / 2 - buttonWidth / 2;

    setButtonStyle(easyB, easyBT, "Easy", xPos - 250, height / 7 + 70);
    setButtonStyle(normalB, normalBT, "Normal", xPos, height / 7 + 70);
    setButtonStyle(hardB, hardBT, "Hard", xPos + 250, height / 7 + 70);

    setButtonStyle(fontB1, fontBT1, "Roboto-Italic", xPos - 250, height / 2.5 + 70);
    setButtonStyle(fontB2, fontBT2, "Roboto-Mono", xPos, height / 2.5 + 70);
    setButtonStyle(fontB3, fontBT3, "Tiny5", xPos + 250, height / 2.5 + 70);

    setButtonStyle(fontSizeToggleB, fontSizeToggleBT, "Font Size (24)", xPos, height / 2 + 140);

    setButtonStyle(backB, backBT, "Back to Menu", xPos, height - buttonHeight - buttonSpacing);
}

void Options::setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos) {
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

void Options::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(difficultyTitle);
    window.draw(easyB);
    window.draw(normalB);
    window.draw(hardB);
    window.draw(easyBT);
    window.draw(normalBT);
    window.draw(hardBT);

    window.draw(fontTitle);
    window.draw(fontB1);
    window.draw(fontB2);
    window.draw(fontB3);
    window.draw(fontBT1);
    window.draw(fontBT2);
    window.draw(fontBT3);

    window.draw(fontSizeTitle);
    window.draw(fontSizeToggleB);
    window.draw(fontSizeToggleBT);

    window.draw(backB);
    window.draw(backBT);
}

void Options::moveUp() {
    if (selectedIndex > 0) {
        selectedIndex--;
    }
}

void Options::moveDown() {
    if (selectedIndex < 7) {
        selectedIndex++;
    }
}


int Options::getSelectedIndex() const {
    return selectedIndex;
}

bool Options::isBackSelected() const {
    return selectedIndex == 7;
}

const sf::Font& Options::getSelectedFont() const {
    return *selectedFont;
}

int Options::getFontSize() const {
    switch (fontSizeIndex) {
        case 0:
            return 18;
        case 1:
            return 24;
        case 2:
            return 36;
        default:
            return 24;
    }
}

void Options::toggleFontSize() {
    fontSizeIndex = (fontSizeIndex + 1) % 3;
    switch (fontSizeIndex) {
        case 0:
            fontSizeToggleBT.setString("Font Size (18)");
            break;
        case 1:
            fontSizeToggleBT.setString("Font Size (24)");
            break;
        case 2:
            fontSizeToggleBT.setString("Font Size (36)");
            break;
    }
}