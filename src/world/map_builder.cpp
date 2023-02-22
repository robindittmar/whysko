#include "map_builder.h"
#include "map.h"

#include "../engine/logging.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <sstream>

using json = nlohmann::json;

Map MapBuilder::build() {
    Map map;
    map.setup(tileMap);
    map.pushTiles(tiles);
    map.buildMesh();
    return map;
}

MapBuilder& MapBuilder::setTileMap(const std::string& tilemap) {
    tileMap = tilemap;
    return *this;
}

MapBuilder& MapBuilder::setTiles(const std::vector<MapTile>& tilesVector) {
    tiles = tilesVector;
    return *this;
}

MapBuilder& MapBuilder::loadFromFile(const std::string& filename) {
    auto& logging = Logging::instance();
    sf::Clock perfTimer;

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        return *this;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();

    loadFromJson(buffer.str());

    std::stringstream ss;
    ss << "Loaded map " << filename << " in " << perfTimer.getElapsedTime().asMilliseconds() << " ms";
    logging.log(ss.str());

    return *this;
}

MapBuilder& MapBuilder::loadFromJson(const std::string& mapAsJson) {
    auto map = json::parse(mapAsJson);

    std::map<std::string, sf::FloatRect> textureDict;

    tileMap = map["background"]["tile-map"];
    for (const auto& texture: map["background"]["textures"]) {
        textureDict[texture["id"]] = sf::FloatRect(
                texture["x0"],
                texture["y0"],
                texture["x1"],
                texture["y1"]);
    }

    for (const auto& tile: map["background"]["tiles"]) {
        tiles.emplace_back(
                sf::FloatRect(tile["x0"],
                              tile["y0"],
                              tile["x1"],
                              tile["y1"]),
                textureDict[tile["texture"]]);
    }

    return *this;
}
