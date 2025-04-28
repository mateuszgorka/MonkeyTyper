#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

Game::Game(sf::RenderWindow &window, ResultsScreen& resultsScreen)
        : window(window), score(0), gameState(State::MENU), currentDifficulty(Difficulty::NORMAL), wordSpeed(1.5f), resultsScreen(resultsScreen), currentFontSize(24) {


    font.loadFromFile("assets/fonts/Roboto-Italic.ttf");
    backgroundTexture.loadFromFile("assets/Icons/Theme.png");
    backgroundSprite.setTexture(backgroundTexture);

    setupText();
    srand(static_cast<unsigned>(time(nullptr)));  // static cast zamiana na typ float https://www.geeksforgeeks.org/static_cast-in-cpp/
}

void Game::run() {
    std::ifstream inputFile("assets/f1words.txt");


    std::string word;
    while (inputFile >> word) {
        wordsToType.push_back(word);
    }
    inputFile.close();

    sf::Clock clock;
    sf::Time spawnTime = sf::seconds(1.5f);
    gameTimeLimit = sf::seconds(60);
    gameClock.restart();

    while (window.isOpen() && gameState == State::RUNNING) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleInput(event);
        }


        if (gameClock.getElapsedTime() >= gameTimeLimit) {
            showResults();
            gameState = State::RESULTS;
        }

        if (clock.getElapsedTime() >= spawnTime) {
            spawnFlyingWord();
            clock.restart();
        }
        update();
        render();
    }
}

void Game::setupText() {
    userInput.setFont(font);
    userInput.setCharacterSize(24);
    userInput.setPosition(85.f, 540.f);

    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 50.f);
}

void Game::handleInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 32 && event.text.unicode <= 126) {
            char typedChar = static_cast<char>(event.text.unicode);
            userInput.setString(userInput.getString() + typedChar);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace) {
            std::string currentText = userInput.getString().toAnsiString();  // konwertuje unicode do ANSI string source: https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1String.php#ada5d5bba4528aceb0a1e298553e6c30a
            if (!currentText.empty()) {
                currentText.pop_back();
                userInput.setString(currentText);
            }
        } else if (event.key.code == sf::Keyboard::Enter) {
            std::string typedWord = userInput.getString().toAnsiString();
            for (auto it = flyingWords.begin(); it != flyingWords.end(); ++it) {
                std::string flyingWord = it->getString().toAnsiString();
                if (typedWord == flyingWord) {
                    flyingWords.erase(it);
                    score++;
                    break;
                }
            }
            userInput.setString("");
        } else if (event.key.code == sf::Keyboard::Escape) {
            gameState = State::MENU;
        }
    }
}

void Game::update() {
    for (size_t i = 0; i < flyingWords.size(); ++i) {
        flyingWords[i].move(wordSpeed, 0.f);
        if (flyingWords[i].getPosition().x > window.getSize().x) {
            flyingWords.erase(flyingWords.begin() + i);
            score--;
            missedWords++;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));
    window.draw(backgroundSprite);


    for (const auto& word : flyingWords) {
        window.draw(word);
    }
    window.draw(userInput);

    sf::Text information;
    information.setFont(font);
    information.setCharacterSize(13);
    information.setFillColor(sf::Color::Yellow);
    information.setString("Press [ESC] to return");
    information.setPosition(340.0f,5.0f);
    window.draw(information);



    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Punkty: " + std::to_string(score));
    scoreText.setPosition(10.f, 10.f);
    window.draw(scoreText);

    updateTimer();
    window.draw(timerText);

    window.display();
}

void Game::spawnFlyingWord() {
    if (wordsToType.empty()) {
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(currentFontSize);
    text.setString(wordsToType[rand() % wordsToType.size()]);   // -> randomowy numer https://cplusplus.com/reference/cstdlib/rand/
    text.setFillColor(sf::Color::White);
    text.setPosition(-100.f, static_cast<float>(rand() % (window.getSize().y - 100)));  // -> satic cast = wartosc na float

    flyingWords.push_back(text);
}

void Game::setDifficulty(Difficulty difficulty) {
    currentDifficulty = difficulty;
    updateWordSpeed();
}

Game::State Game::getState() const {
    return gameState;
}

void Game::updateTimer() {
    sf::Time elapsed = gameClock.getElapsedTime();
    sf::Time timeLeft = gameTimeLimit - elapsed;

    if (timeLeft <= sf::Time::Zero) {
        timeLeft = sf::Time::Zero;
        showResults();
    }

    int seconds = timeLeft.asSeconds();
    timerText.setString("Czas: " + std::to_string(seconds) + "s");
}

void Game::showResults() {
    std::string difficulty;
    switch (currentDifficulty) {
        case Difficulty::EASY:
            difficulty = "Easy";
            break;
        case Difficulty::NORMAL:
            difficulty = "Normal";
            break;
        case Difficulty::HARD:
            difficulty = "Hard";
            break;
    }
    resultsScreen.show(window, score, missedWords, difficulty);
    gameState = State::MENU;
}

void Game::setState(State newState) {
    gameState = newState;
}

void Game::updateWordSpeed() {
    switch (currentDifficulty) {
        case Difficulty::EASY:
            wordSpeed = 1.0f;
            spawnTime = sf::seconds(2.0f);
            break;
        case Difficulty::NORMAL:
            wordSpeed = 1.5f;
            spawnTime = sf::seconds(1.0f);
            break;
        case Difficulty::HARD:
            wordSpeed = 2.5f;
            spawnTime = sf::seconds(0.5f);
            break;
    }
}

void Game::setFlyingWordsFont(const sf::Font& font, int size) {
    this->font = font;
    this->currentFontSize = size;
    for (auto& word : flyingWords) {
        word.setFont(font);
        word.setCharacterSize(size);
    }
}

void Game::resetGame() {
    score = 0;
    missedWords = 0;
    gameState = State::MENU;
    wordsToType.clear();
    flyingWords.clear();
    userInput.setString("");
    timerText.setString("Czas: 0s");
    gameClock.restart();
}
