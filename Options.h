#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Options {
public:
    Options(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    bool isBackSelected() const;
    const sf::Font& getSelectedFont() const;
    int getFontSize() const;
    void toggleFontSize();


    sf::Font font1;
    sf::Font font2;
    sf::Font font3;

    sf::RectangleShape easyB;
    sf::RectangleShape normalB;
    sf::RectangleShape hardB;
    sf::RectangleShape backB;
    sf::RectangleShape fontB1;
    sf::RectangleShape fontB2;
    sf::RectangleShape fontB3;
    sf::RectangleShape fontSizeToggleB;

    sf::Font* selectedFont; // -> tutaj wykorzystujemy pointer dla wybranej czcionki!

private:
    int selectedIndex;
    sf::Font font;
    sf::Text title;
    sf::Text difficultyTitle;
    sf::Text fontTitle;
    sf::Text fontSizeTitle;
    sf::Text easyBT;
    sf::Text normalBT;
    sf::Text hardBT;
    sf::Text backBT;
    sf::Text fontBT1;
    sf::Text fontBT2;
    sf::Text fontBT3;
    sf::Text fontSizeToggleBT;
    int fontSizeIndex;



    void positionButtons(float width, float height);
    void setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos);
};

#endif
