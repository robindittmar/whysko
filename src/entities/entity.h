#ifndef WHYSKO_ENTITY_H
#define WHYSKO_ENTITY_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Entity {
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void think(float deltaTime) = 0;
    virtual void render(sf::RenderTarget& renderTarget);

    inline uint64_t getId() const;
    inline void setId(uint64_t i);

    inline bool getActive() const;
    inline void setActive(bool a);

    inline sf::Sprite& getSprite();

protected:
    uint64_t id = 0;
    bool active = true;
    sf::Sprite sprite;
};

uint64_t Entity::getId() const {
    return id;
}

void Entity::setId(uint64_t i) {
    id = i;
}

bool Entity::getActive() const {
    return active;
}

void Entity::setActive(bool a) {
    active = a;
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}

#endif//WHYSKO_ENTITY_H
