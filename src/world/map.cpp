#include "map.h"
#include "SFML/Graphics/Text.hpp"


void Map::setup(const std::string& bgTexture) {
    texture = Engine::instance().getResourceManager().loadTexture(bgTexture);

    bgVertices.setPrimitiveType(sf::Quads);
}

void Map::pushTiles(const std::vector<MapTile>& mapTiles) {
    tiles.insert(tiles.end(), mapTiles.begin(), mapTiles.end());
}

void Map::buildMesh() {
    std::vector<MapTile>::size_type tilesCount = tiles.size();

    bgVertices.resize(tilesCount * 4);
    for (std::vector<MapTile>::size_type i = 0; i != tilesCount; i++) {
        tiles[i].writeVertexQuad(&bgVertices[i * 4]);
    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(bgVertices, states);
}
