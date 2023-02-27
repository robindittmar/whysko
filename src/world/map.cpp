#include "map.h"
#include "SFML/Graphics/Text.hpp"


void Map::setup(const std::string& bgTexture) {
    texture = Engine::instance().getResourceManager().loadTexture(bgTexture);

    bgVertices.setPrimitiveType(sf::Quads);
    collidableVertices.setPrimitiveType(sf::Quads);
}

void Map::pushTiles(const std::vector<MapTile>& mapTiles) {
    tiles.insert(tiles.end(), mapTiles.begin(), mapTiles.end());
    std::for_each(tiles.begin(), tiles.end(), [this](auto& t) {
        if (t.hasCollision()) {
            collidableTiles.push_back(t);
        }
    });
}

void Map::buildMesh() {
    std::vector<MapTile>::size_type tilesCount = tiles.size();

    bgVertices.resize(tilesCount * 4);
    for (std::vector<MapTile>::size_type i = 0; i != tilesCount; i++) {
        tiles[i].writeVertexQuad(&bgVertices[i * 4]);
    }

    if (drawCollidables) {
        buildDebugMesh();
    }
}

bool Map::collides(const sf::FloatRect& bounds) const {
    return std::any_of(collidableTiles.cbegin(), collidableTiles.cend(), [&bounds](auto& tile) {
        return tile.getCollisionBounds().intersects(bounds);
    });
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(bgVertices, states);

    if (drawCollidables) {
        states.texture = nullptr;
        target.draw(collidableVertices, states);
    }
}

void Map::buildDebugMesh() {
    std::vector<MapTile>::size_type tilesCount = collidableTiles.size();

    collidableVertices.resize(tilesCount * 4);
    for (std::vector<MapTile>::size_type i = 0; i != tilesCount; i++) {
        collidableTiles[i].writeDebugVertexQuad(&collidableVertices[i * 4]);
    }
}
