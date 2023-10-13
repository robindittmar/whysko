#ifndef WHYSKO_PLAYER_H
#define WHYSKO_PLAYER_H

#include "SFML/Graphics/VertexArray.hpp"
#include "entity.h"


constexpr float MAX_SHOOT_COOLDOWN = 0.1f;


class Player : public Entity {
public:
    Player();
    ~Player() override = default;

    void think(float deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

    inline void setDrawHitbox(bool draw);

private:
    void move(float deltaTime, sf::Vector2f desiredVelocity);
    void shoot(float deltaTime);

    void setupHitbox();

    sf::Vector2f velocity;
    bool interacting = false;

    float shootCooldown = 0.0f;

    bool drawHitbox = false;
    sf::VertexArray hitbox;
};


void Player::setDrawHitbox(bool draw) {
    drawHitbox = draw;
}


#endif//WHYSKO_PLAYER_H
