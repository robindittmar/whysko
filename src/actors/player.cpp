#include "player.h"
#include "../engine/engine.h"
#include "../engine/input_manager.h"
#include "work_intent.h"

Player::Player() {
    _sprite.setTexture(Engine::instance().getResourceManager().loadTexture("img/cat2.png"));
    _sprite.setOrigin(32.0f, 32.0f);
    _sprite.setPosition(600.0f, 600.0f);
    _sprite.setScale(5.0f, 5.0f);
}

void Player::think(float delta) {
    sf::Vector2f desiredVelocity = {0.f, 0.f};
    float speed = 250.0f;
    auto& inputManager = InputManager::instance();

    if (inputManager.interact()) {
        if (curIntent && curIntent->getId() == IntentId::Work) {
            Actor::think(delta);
        } else {
            pushIntent(std::make_shared<WorkIntent>(10.0f));
            Actor::think(delta);
        }

    } else {
        if (inputManager.modifier()) {
            speed *= 1.7f;
        }
        if (inputManager.moveUp()) {
            desiredVelocity.y -= speed;
        }
        if (inputManager.moveDown()) {
            desiredVelocity.y += speed;
        }
        if (inputManager.moveLeft()) {
            desiredVelocity.x -= speed;
        }
        if (inputManager.moveRight()) {
            desiredVelocity.x += speed;
        }

        float len = sqrt(desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y);
        if (len > 0) {
            desiredVelocity.x *= std::abs(desiredVelocity.x / len);
            desiredVelocity.y *= std::abs(desiredVelocity.y / len);

            desiredVelocity.x *= delta;
            desiredVelocity.y *= delta;

            _sprite.move(desiredVelocity);
        }
    }
}
