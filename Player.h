#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Bullet.h"

class Player
{
public:
    Player();
    void handleInput();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    void shoot(); // new method
    std::vector<Bullet>& getBullets(); // getter method
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    float rotationSpeed;
    std::vector<Bullet> bullets;

    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;

    sf::Clock fireClock;
    sf::Time fireCooldown = sf::seconds(0.25f);
};
