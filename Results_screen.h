#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

class ResultsScreen {
public:
    ResultsScreen(float width, float height);
    void show(sf::RenderWindow& window, int score, int missedWord, const std::string& difficulty);


private:
    bool finished;
    sf::Font font;
    sf::Text resultText;
    sf::Text menuText;
    sf::Text highScoresTitle;
    sf::Text missedWordsText;
    sf::Text difficultyText;
    sf::RectangleShape backB;
    sf::Text backBT;
    std::vector<sf::Text> highScoresTexts;


    void setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos);
};

#endif
