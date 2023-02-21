#ifndef WHYSKO_RESOURCE_MANAGER_H
#define WHYSKO_RESOURCE_MANAGER_H

#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

using TextureCache = std::unordered_map<std::string, sf::Texture>;
using FontCache = std::unordered_map<std::string, sf::Font>;

class ResourceManager {
public:
    ResourceManager() = default;
    ResourceManager(ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ~ResourceManager() = default;

    sf::Texture& loadTexture(const std::string& filename);
    sf::Font& loadFont(const std::string& filename);

private:
    TextureCache textureCache;
    FontCache fontCache;
};


#endif//WHYSKO_RESOURCE_MANAGER_H
