// Bullet.h

#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Vector2f position, float rotation);

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;
    const sf::CircleShape& getShape() const;

private:
    sf::CircleShape shape;
    float speed;
};
