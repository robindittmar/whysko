#ifndef WHYSKO_MAP_H
#define WHYSKO_MAP_H

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "engine.h"
#include "map_tile.h"


constexpr uint32_t MAP_WIDTH = 32;
constexpr uint32_t MAP_HEIGHT = 32;
constexpr uint32_t MAP_COUNT_TILES = MAP_WIDTH * MAP_HEIGHT;

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map() = default;
    ~Map() override = default;

    void setup(const std::string& bgTexture);

    void pushTiles(const std::vector<MapTile>& mapTiles);
    void buildMesh();

    void render(sf::RenderTarget& renderTarget) const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    std::vector<MapTile> tiles;

    sf::Texture texture;
    sf::VertexArray bgVertices;
};

#endif//WHYSKO_MAP_H
