#ifndef WHYSKO_BULLET_H
#define WHYSKO_BULLET_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "entity.h"


class Bullet : public Entity {
public:
    Bullet(sf::Vector2f pos, sf::Vector2f vel);

    void think(float deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;

    sf::RectangleShape shape;
};


#endif//WHYSKO_BULLET_H
