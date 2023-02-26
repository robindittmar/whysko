#include "settings_repository.h"
#include <nlohmann/json.hpp>
#include <sstream>

#include "input_settings.h"

using json = nlohmann::json;

constexpr const char* CONFIG_FILENAME = "cfg/input-config.json";

bool SettingsRepository::loadInputSettings() {
    std::ifstream ifs(CONFIG_FILENAME);
    if (!ifs.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();

    return parseInputJson(buffer.str());
}

bool SettingsRepository::writeInputSettings() {
    std::ofstream ofs(CONFIG_FILENAME, std::ios::out);
    if (!ofs.is_open()) {
        return false;
    }

    return dumpInputJson(ofs);
}

bool SettingsRepository::parseInputJson(const std::string& buffer) {
    auto& inputSettings = InputSettings::instance();

    auto config = json::parse(buffer);

    inputSettings.keyMoveUp = config["keys"].value("move-up", inputSettings.keyMoveUp);
    inputSettings.keyMoveDown = config["keys"].value("move-down", inputSettings.keyMoveDown);
    inputSettings.keyMoveLeft = config["keys"].value("move-left", inputSettings.keyMoveLeft);
    inputSettings.keyMoveRight = config["keys"].value("move-right", inputSettings.keyMoveRight);
    inputSettings.keyInteract = config["keys"].value("interact", inputSettings.keyInteract);
    inputSettings.keyMod = config["keys"].value("modifier", inputSettings.keyMod);

    return true;
}

bool SettingsRepository::dumpInputJson(std::ofstream& ofs) {
    auto& inputSettings = InputSettings::instance();

    auto config = json();
    config["keys"]["move-up"] = inputSettings.keyMoveUp;
    config["keys"]["move-down"] = inputSettings.keyMoveDown;
    config["keys"]["move-left"] = inputSettings.keyMoveLeft;
    config["keys"]["move-right"] = inputSettings.keyMoveRight;
    config["keys"]["interact"] = inputSettings.keyInteract;
    config["keys"]["modifier"] = inputSettings.keyMod;

    auto dump = config.dump(2);
    ofs.write(dump.c_str(), dump.length());

    return true;
}
