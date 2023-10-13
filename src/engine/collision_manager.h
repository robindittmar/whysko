#ifndef WHYSKO_COLLISION_MANAGER_H
#define WHYSKO_COLLISION_MANAGER_H

#include "SFML/Graphics/Rect.hpp"
#include <vector>


class GameScene;

class CollisionManager {
public:
    explicit CollisionManager(GameScene& scene);
    ~CollisionManager() = default;

    sf::Vector2f fixMove(const sf::Vector2f& velocity, const sf::FloatRect& rect, const std::vector<sf::FloatRect>& collision);
    bool collidesWithMap(const sf::FloatRect& rect, std::vector<sf::FloatRect>& out);

private:
    GameScene& gameScene;
};


#endif//WHYSKO_COLLISION_MANAGER_H
