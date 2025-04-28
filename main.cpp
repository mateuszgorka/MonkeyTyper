#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Background.h"
#include "Menu.h"
#include "Game.h"
#include "Options.h"
#include "Results_screen.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum class State {
    MENU,
    RUNNING,
    OPTIONS,
    EXIT
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Formula-Typer");
    window.setFramerateLimit(60);
    Background background("assets/Icons/background1.gif", "assets/frames/",window);

    sf::Image icon;
    icon.loadFromFile("assets/Icons/LogoMiniature.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    std::vector<sf::Texture> frames;




    State appState = State::MENU;
    Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);
    ResultsScreen resultsScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
    Game game(window, resultsScreen);
    Options options(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            switch (appState) {
                case State::MENU:
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse = sf::Mouse::getPosition(window);
                            if (menu.startB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::RUNNING;
                                game.setState(Game::State::RUNNING);
                            } else if (menu.optionsB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::OPTIONS;
                            } else if (menu.exitB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::EXIT;
                                window.close();
                            }
                        }
                    }
                    break;

                case State::OPTIONS:
                    options.moveUp();
                    options.moveDown();
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse = sf::Mouse::getPosition(window);
                            if (options.easyB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                game.setDifficulty(Game::Difficulty::EASY);
                            } else if (options.normalB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {   // -> Vector2f 2 wymiarowe vectory  https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Vector2.php
                                game.setDifficulty(Game::Difficulty::NORMAL);
                            } else if (options.hardB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                game.setDifficulty(Game::Difficulty::HARD);
                            } else if (options.fontB1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                options.selectedFont = &options.font1;
                                game.setFlyingWordsFont(options.getSelectedFont(), options.getFontSize());
                            } else if (options.fontB2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                options.selectedFont = &options.font2;
                                game.setFlyingWordsFont(options.getSelectedFont(), options.getFontSize());
                            } else if (options.fontB3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                options.selectedFont = &options.font3;
                                game.setFlyingWordsFont(options.getSelectedFont(), options.getFontSize());
                            } else if (options.fontSizeToggleB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {  // getGlobalBounds()  referencja do klasy sprite https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sprite.php
                                options.toggleFontSize();
                                game.setFlyingWordsFont(options.getSelectedFont(), options.getFontSize());
                            } else if (options.backB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::MENU;
                            }
                        }
                    }
                    break;

                case State::RUNNING:
                    game.run();
                    if (game.getState() == Game::State::MENU) {
                        appState = State::MENU;
                        game.resetGame();  // -> wazne zeby zresetowac po kazdej grze, zeby zespawnowane slowa dalej nie lecialy
                    }
                    break;

                case State::EXIT:
                    window.close();
                    break;
            }
        }

        background.update();
        window.clear();
        background.draw(window);

        if (appState == State::MENU) {
            menu.draw(window);
        } else if (appState == State::OPTIONS) {
            options.draw(window);
        }

        window.display();
    }
}
