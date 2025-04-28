#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Results_screen.h"

class Game {
public:
    enum class State {
        MENU,
        RUNNING,
        OPTIONS,
        EXIT,
        RESULTS
    };

    enum class Difficulty {
        EASY,
        NORMAL,
        HARD
    };

    Game(sf::RenderWindow &window, ResultsScreen &resultsScreen);
    void run();
    void setDifficulty(Difficulty difficulty);
    State getState() const;
    void showResults();
    void setState(State newState);
    void setFlyingWordsFont(const sf::Font& font, int size);
    void resetGame();

    void render();

private:
    void setupText();
    void handleInput(sf::Event& event);
    void update();
    void spawnFlyingWord();
    void updateWordSpeed();
    void updateTimer();

    sf::RenderWindow& window;
    ResultsScreen& resultsScreen;


public:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;    // sprite rysowalna reprezentazja tekstury (narzedzie sfml) https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sprite.php
    sf::Font font;
    sf::Text userInput;
    sf::Text timerText;
    sf::Text resultText;
    sf::Clock gameClock;
    sf::Time gameTimeLimit;

    State gameState;
    Difficulty currentDifficulty;

    std::vector<std::string> wordsToType;
    std::vector<sf::Text> flyingWords;
    int score;
    int missedWords;
    sf::Time spawnTime;
    float wordSpeed;
    int currentFontSize;




};

#endif
