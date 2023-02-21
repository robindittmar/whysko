#ifndef WHYSKO_MAP_H
#define WHYSKO_MAP_H

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Transformable.hpp"

#include "engine.h"


constexpr uint32_t MAP_WIDTH = 32;
constexpr uint32_t MAP_HEIGHT = 32;
constexpr uint32_t MAP_COUNT_TILES = MAP_WIDTH * MAP_HEIGHT;

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map() = default;
    ~Map() override = default;

    void Setup(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    void Render(sf::RenderTarget& renderTarget) const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Texture texture;
    sf::VertexArray vertices;
};

#endif //WHYSKO_MAP_H
