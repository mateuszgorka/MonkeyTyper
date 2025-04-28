#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Background {
public:
    Background(const std::string& staticFilePath, const std::string& gifFilePath, sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Texture staticTexture;
    sf::Sprite staticSprite;

    std::vector<sf::Texture> gifFrames;
    sf::Sprite gifSprite;
    int currentFrame;
    sf::Clock clock;
    sf::Time frameTime;
};

#endif
