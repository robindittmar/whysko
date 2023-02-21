#include "map.h"
#include "SFML/Graphics/Text.hpp"


void Map::setup(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
    texture = Engine::instance().getResourceManager().loadTexture("img/graphics-vertex-array-tilemap-tileset.png");

    bgVertices.setPrimitiveType(sf::Quads);
    bgVertices.resize(width * height * 4);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (texture.getSize().x / tileSize.x);
            int tv = tileNumber / (texture.getSize().x / tileSize.x);

            sf::Vertex* quad = &bgVertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
}

void Map::render(sf::RenderTarget& renderTarget) const {
    //    for (const auto& tile : backgroundLayer) {
    //        renderTarget.draw(tile);
    //    }
    //    for (const auto& tileDebug : backgroundLayerDebugText) {
    //        renderTarget.draw(tileDebug);
    //    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(bgVertices, states);
}
