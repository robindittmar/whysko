#ifndef WHYSKO_RESOURCE_MANAGER_H
#define WHYSKO_RESOURCE_MANAGER_H

#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

using TextureCache = std::unordered_map<std::string, sf::Texture>;
using FontCache = std::unordered_map<std::string, sf::Font>;

class ResourceManager {
public:
    ResourceManager() = default;
    ResourceManager(ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ~ResourceManager() = default;

    sf::Texture& LoadTexture(const std::string& filename);
    sf::Font& LoadFont(const std::string& filename);
private:
    TextureCache textureCache;
    FontCache fontCache;
};


#endif //WHYSKO_RESOURCE_MANAGER_H
