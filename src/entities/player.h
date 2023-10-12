#ifndef WHYSKO_PLAYER_H
#define WHYSKO_PLAYER_H

#include "SFML/Graphics/VertexArray.hpp"
#include "actor.h"


class Player : public Actor {
public:
    Player();
    ~Player() override = default;

    void think(float deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

    inline void setDrawHitbox(bool draw);

private:
    void setupHitbox();

    bool interacting = false;

    bool drawHitbox = false;
    sf::VertexArray hitbox;
};


void Player::setDrawHitbox(bool draw) {
    drawHitbox = draw;
}


#endif//WHYSKO_PLAYER_H
