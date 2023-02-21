#ifndef WHYSKO_MAP_H
#define WHYSKO_MAP_H

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "engine.h"


constexpr uint32_t MAP_WIDTH = 32;
constexpr uint32_t MAP_HEIGHT = 32;
constexpr uint32_t MAP_COUNT_TILES = MAP_WIDTH * MAP_HEIGHT;

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map() = default;
    ~Map() override = default;

    void setup(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    void render(sf::RenderTarget& renderTarget) const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Texture texture;
    sf::VertexArray bgVertices;
};

#endif//WHYSKO_MAP_H
