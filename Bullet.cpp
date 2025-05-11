#include "Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f position, float rotation) : speed(500.f) {
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(5.f, 5.f);
    shape.setPosition(position);
    shape.setRotation(rotation);
}

void Bullet::update(sf::Time deltaTime) {
    float angle = shape.getRotation() - 90.f;
    float rad = angle * 3.14159265f / 180.f;
    float dx = std::cos(rad) * speed * deltaTime.asSeconds();
    float dy = std::sin(rad) * speed * deltaTime.asSeconds();
    shape.move(dx, dy);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Bullet::isOffScreen() const {
    auto pos = shape.getPosition();
    return pos.x < 0 || pos.x > 800 || pos.y < 0 || pos.y > 600;
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}

const sf::CircleShape& Bullet::getShape() const {
    return shape;
}
