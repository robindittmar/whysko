#include "map.h"
#include "SFML/Graphics/Text.hpp"


void Map::Setup() {
    backgroundLayer.reserve(MAP_COUNT_TILES);

    sf::Font& fnt = Engine::Instance().GetResourceManager().LoadFont("fnt/FiraCode-Regular.ttf");
    sf::Texture& tex = Engine::Instance().GetResourceManager().LoadTexture("img/tile2.png");

    for (int i = 0; i < MAP_COUNT_TILES; i++) {
        sf::Sprite tile(tex);
        tile.setPosition((float)((i % MAP_WIDTH) * 64), (float)((i / MAP_WIDTH) * 64));

        sf::Text text(std::to_string(i), fnt, 12);
        text.setPosition((float)((i % MAP_WIDTH) * 64), (float)((i / MAP_WIDTH) * 64));

        backgroundLayer.push_back(std::move(tile));
        backgroundLayerDebugText.push_back(std::move(text));
    }
}

void Map::Render(sf::RenderTarget& renderTarget) const {
    for (const auto& tile : backgroundLayer) {
        renderTarget.draw(tile);
    }
    for (const auto& tileDebug : backgroundLayerDebugText) {
        renderTarget.draw(tileDebug);
    }
}

void Map::RenderForeground(sf::RenderTarget& renderTarget) const {
}
