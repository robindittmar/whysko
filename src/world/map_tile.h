#ifndef WHYSKO_MAP_TILE_H
#define WHYSKO_MAP_TILE_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Vertex.hpp"


class MapTile {
public:
    MapTile(sf::FloatRect wrldRect, sf::FloatRect texRect, bool hasCollision, sf::FloatRect colRect);
    ~MapTile() = default;

    void writeVertexQuad(sf::Vertex* buffer) const;
    void writeDebugVertexQuad(sf::Vertex* buffer) const;

    inline bool hasCollision() const;
    inline sf::FloatRect getCollisionBounds() const;

private:
    sf::FloatRect worldRect;
    sf::FloatRect textureRect;
    bool collision;
    sf::FloatRect collisionRect;
};

bool MapTile::hasCollision() const {
    return collision;
}

sf::FloatRect MapTile::getCollisionBounds() const {
    return collisionRect;
}

#endif//WHYSKO_MAP_TILE_H
