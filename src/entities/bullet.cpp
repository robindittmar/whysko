#include "bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel)
    : velocity(vel), lifetime(0.0f), circle(10.0f) {
    circle.setPosition(pos);
    circle.setFillColor(sf::Color(100, 250, 50));
}

void Bullet::think(float deltaTime) {
    circle.move(velocity * deltaTime);

    lifetime += deltaTime;
    if (lifetime > 10.0f) {
        active = false;
    }
}

void Bullet::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(circle);
}
