#include "bullet.h"
#include "../engine/engine.h"
#include <cmath>

constexpr const float PI = 3.14159265359f;

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel)
    : position(pos), velocity(vel), lifetime(0.0f) {
    auto& e = Engine::instance();

    shape.setPosition(position);
    shape.setFillColor(sf::Color(
        (uint8_t)(e.getRandomNumber() * 255.f),
        (uint8_t)(e.getRandomNumber() * 255.f),
        (uint8_t)(e.getRandomNumber() * 255.f)));
}

void Bullet::think(float deltaTime) {
    float rot = 90.f - atan2(velocity.x, velocity.y) * (180.0f / PI);

    shape.move(velocity);
    shape.setSize(sf::Vector2f(20.f * sqrt(velocity.x * velocity.x + velocity.y * velocity.y), 5.f));
    shape.setRotation(rot);

    lifetime += deltaTime;
    if (lifetime > 10.0f) {
        active = false;
    }
}

void Bullet::render(sf::RenderTarget& renderTarget) {
    //    renderTarget.draw(line, 2, sf::Lines);
    renderTarget.draw(shape);
}
