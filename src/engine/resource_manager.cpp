#include "resource_manager.h"


sf::Texture& ResourceManager::loadTexture(const std::string& filename) {
    if (textureCache.find(filename) != textureCache.end()) {
        return textureCache[filename];
    }

    sf::Texture tex;
    tex.loadFromFile(filename);

    textureCache[filename] = tex;
    return textureCache[filename];
}

sf::Font& ResourceManager::loadFont(const std::string& filename) {
    if (fontCache.find(filename) != fontCache.end()) {
        return fontCache[filename];
    }

    sf::Font font;
    font.loadFromFile(filename);

    fontCache[filename] = font;
    return fontCache[filename];
}
