#pragma once
#include <SFML/Graphics.hpp>

class Asteroid
{
public:
    Asteroid(float x, const sf::Texture& texture);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    float speed;
};