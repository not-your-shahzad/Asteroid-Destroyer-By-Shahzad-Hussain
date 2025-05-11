#include "Asteroid.h"
#include <cstdlib>

Asteroid::Asteroid(float x, const sf::Texture& texture)
    : speed(100.f + std::rand() % 100)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, -50.f); // Start above the screen
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

void Asteroid::update(sf::Time deltaTime)
{
    sprite.move(0.f, speed * deltaTime.asSeconds());
}

void Asteroid::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Asteroid::isOffScreen() const
{
    return sprite.getPosition().y > 600.f;
}

sf::FloatRect Asteroid::getBounds() const
{
    return sprite.getGlobalBounds();
}
