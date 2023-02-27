#ifndef WHYSKO_MAP_H
#define WHYSKO_MAP_H

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "../engine/engine.h"
#include "map_tile.h"


class Map : public sf::Drawable, public sf::Transformable {
public:
    Map() = default;
    ~Map() override = default;

    void setup(const std::string& bgTexture);

    void pushTiles(const std::vector<MapTile>& mapTiles);
    void buildMesh();

    bool collides(const sf::FloatRect& bounds) const;

    inline bool getDrawCollidables() const;
    inline void setDrawCollidables(bool draw);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void buildDebugMesh();

    std::vector<MapTile> tiles;
    std::vector<MapTile> collidableTiles;

    sf::Texture texture;
    sf::VertexArray bgVertices;

    bool drawCollidables;
    sf::VertexArray collidableVertices;
};

bool Map::getDrawCollidables() const {
    return drawCollidables;
}

void Map::setDrawCollidables(bool draw) {
    drawCollidables = draw;
}

#endif//WHYSKO_MAP_H
