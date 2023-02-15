#ifndef WHYSKO_MAP_H
#define WHYSKO_MAP_H

#include <SFML/Graphics/Sprite.hpp>

#include "engine.h"


constexpr uint32_t MAP_WIDTH = 32;
constexpr uint32_t MAP_HEIGHT = 32;
constexpr uint32_t MAP_COUNT_TILES = MAP_WIDTH * MAP_HEIGHT;

class Map {
public:
    Map() = default;
    ~Map() = default;

    void Setup();

    void RenderBackground(sf::RenderTarget& renderTarget) const;
    void RenderForeground(sf::RenderTarget& renderTarget) const;
private:
    std::vector<sf::Text> backgroundLayerDebugText;
    std::vector<sf::Sprite> backgroundLayer;
};

#endif //WHYSKO_MAP_H
