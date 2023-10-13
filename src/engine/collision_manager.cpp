#include "collision_manager.h"
#include "../scenes/game_scene.h"

CollisionManager::CollisionManager(GameScene& scene)
    : gameScene(scene) {}

sf::Vector2f CollisionManager::fixMove(const sf::Vector2f& velocity, const sf::FloatRect& rect, const std::vector<sf::FloatRect>& collision) {
    sf::Vector2f fixVelocity(0.0f, 0.0f);

    for (auto& colliding : collision) {
        auto curRect = rect;

        // Reset position
        curRect.left -= velocity.x;
        curRect.top -= velocity.y;

        // Move only on x-axis
        if (velocity.x != 0.0f) {
            curRect.left += velocity.x;
            if (curRect.intersects(colliding)) {
                // If we collide again, correct properly.
                float fixVelX;
                if (velocity.x > 0.f) {
                    fixVelX = -(curRect.left + curRect.width) - colliding.left;
                } else {
                    fixVelX = (colliding.left + colliding.width) - curRect.left;
                }

                if (abs(fixVelocity.x) < abs(fixVelX)) {
                    fixVelocity.x = fixVelX;
                }
            }
            curRect.left -= velocity.x;
        }

        if (velocity.y != 0.0f) {
            // Move only on y-axis
            curRect.top += velocity.y;
            if (curRect.intersects(colliding)) {
                // If we collide again, correct properly.
                float fixVelY;
                if (velocity.y > 0.f) {
                    fixVelY = -(curRect.top + curRect.height) - colliding.top;
                } else {
                    fixVelY = (colliding.top + colliding.height) - curRect.top;
                }

                if (abs(fixVelocity.y) < abs(fixVelY)) {
                    fixVelocity.y = fixVelY;
                }
            }
            curRect.top -= velocity.y;
        }
    }

    return fixVelocity;
}

bool CollisionManager::collidesWithMap(const sf::FloatRect& rect, std::vector<sf::FloatRect>& out) {
    return gameScene.getMap().collides(rect, out);
}
