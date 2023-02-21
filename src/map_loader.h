#ifndef WHYSKO_MAP_LOADER_H
#define WHYSKO_MAP_LOADER_H

#include "map.h"
#include "map_tile.h"
#include <string>
#include <vector>

class MapLoader {
public:
    MapLoader() = default;
    ~MapLoader() = default;

    void loadFromFile(const std::string& file);
    void loadFromJson(const std::string& mapAsJson);

    void apply(Map& map) const;

private:
    std::string tileMap;
    std::vector<MapTile> tiles;
};


#endif//WHYSKO_MAP_LOADER_H
