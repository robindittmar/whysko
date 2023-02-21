#ifndef WHYSKO_MAP_TILE_H
#define WHYSKO_MAP_TILE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>


class MapTile {
public:
    MapTile(sf::FloatRect wrldRect, sf::FloatRect texRect);
    ~MapTile() = default;

    void writeVertexQuad(sf::Vertex* buffer) const;

private:
    sf::FloatRect worldRect;
    sf::FloatRect textureRect;
};


#endif//WHYSKO_MAP_TILE_H
