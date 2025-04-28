#include "Background.h"
#include <iostream>
#include <string>

Background::Background(const std::string& staticFilePath, const std::string& gifFilePath, sf::RenderWindow& window)
        : currentFrame(0), frameTime(sf::seconds(0.03f)) {


    staticTexture.loadFromFile(staticFilePath);
    staticSprite.setTexture(staticTexture);


    for (int i = 0; i < 179; ++i) {
        sf::Texture texture;
        std::string filename = gifFilePath + std::to_string(i) + ".gif";
        if (texture.loadFromFile(filename)) {
            gifFrames.push_back(texture);
        }
    }
}

void Background::update() {
    if (clock.getElapsedTime() >= frameTime) {
        currentFrame = (currentFrame + 1) % gifFrames.size();
        gifSprite.setTexture(gifFrames[currentFrame]);
        clock.restart();
    }
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(staticSprite);
    window.draw(gifSprite);
}
