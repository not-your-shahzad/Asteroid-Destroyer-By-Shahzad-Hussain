#include "Player.h"
#include <iostream>
#include <SFML/Audio.hpp>

Player::Player()
    : speed(200.f), rotationSpeed(100.f)
{
    if (!texture.loadFromFile("Assets/textures/player.png"))
    {
        std::cerr << "Error loading player texture\n";
    }

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(400.f, 500.f); // Near bottom center

    if (!shootBuffer.loadFromFile("Assets/audio/shoot.wav")) {
        std::cerr << "Error loading shoot.wav\n";
    }
    shootSound.setBuffer(shootBuffer);
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite.move(-speed * 0.01f, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.move(speed * 0.01f, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite.rotate(-rotationSpeed * 0.01f); // counterclockwise
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite.rotate(rotationSpeed * 0.01f); // clockwise
    }
 
}

void Player::update(sf::Time deltaTime)
{
    handleInput();

    // Fire bullets with Space or Left Mouse
    static bool canShoot = true;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        if (fireClock.getElapsedTime() >= fireCooldown)
        {
            shoot();
            fireClock.restart();
        }
    }


    // Update all bullets
    for (auto& bullet : bullets)
        bullet.update(deltaTime);

    // Remove off-screen bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet& b) { return b.isOffScreen(); }),
        bullets.end());
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    for (auto& bullet : bullets)
        bullet.draw(window);
}

void Player::shoot()
{
    bullets.emplace_back(sprite.getPosition(), sprite.getRotation());
    shootSound.play();
}

std::vector<Bullet>& Player::getBullets()
{
    return bullets;
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}
