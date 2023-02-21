#include "map_loader.h"
#include "logging.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

void MapLoader::loadFromFile(const std::string& file) {
    auto& logging = Logging::instance();
    sf::Clock perfTimer;

    std::ifstream ifs(file);
    if (!ifs.is_open()) {
        return;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();

    loadFromJson(buffer.str());

    std::stringstream ss;
    ss << "Loaded map " << file << " in " << perfTimer.getElapsedTime().asMilliseconds() << " ms";
    logging.log(ss.str());
}

void MapLoader::loadFromJson(const std::string& mapAsJson) {
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
}

void MapLoader::apply(Map& map) const {
    map.setup(tileMap);
    map.pushTiles(tiles);
    map.buildMesh();
}
