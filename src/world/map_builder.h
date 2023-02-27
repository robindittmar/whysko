#ifndef WHYSKO_MAP_BUILDER_H
#define WHYSKO_MAP_BUILDER_H

#include "map_tile.h"
#include <string>
#include <vector>

class Map;

class MapBuilder {
public:
    MapBuilder() = default;
    ~MapBuilder() = default;

    Map build();

    MapBuilder& setTileMap(const std::string& tilemap);
    MapBuilder& setTiles(const std::vector<MapTile>& tilesVector);

    MapBuilder& setDrawDebugInfo(bool draw);

    MapBuilder& loadFromFile(const std::string& filename);
    MapBuilder& loadFromJson(const std::string& mapAsJson);

private:
    std::string tileMap;
    std::vector<MapTile> tiles;
    bool drawDebugInfo;
};


#endif//WHYSKO_MAP_BUILDER_H
