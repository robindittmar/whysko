#include "player.h"
#include "../engine/engine.h"
#include "../engine/input_manager.h"
#include "../scenes/game_scene.h"
#include "work_intent.h"
#include <cmath>

Player::Player() {
    _sprite.setTexture(Engine::instance().getResourceManager().loadTexture("img/cat2.png"));
    _sprite.setOrigin(32.0f, 32.0f);
    _sprite.setPosition(600.0f, 600.0f);
    _sprite.setScale(5.0f, 5.0f);

    hitbox.resize(5);
    hitbox.setPrimitiveType(sf::LineStrip);
}

void Player::think(float delta) {
    sf::Vector2f desiredVelocity = {0.f, 0.f};
    float speed = 250.0f;
    auto& inputManager = InputManager::instance();

    if (inputManager.interact()) {
        if (curIntent && curIntent->getId() == IntentId::Work) {
            Actor::think(delta);
        } else {
            interacting = true;
            pushIntent(std::make_shared<WorkIntent>(10.0f));
            Actor::think(delta);
        }

    } else {
        if (interacting) {
            if (curIntent && curIntent->getId() == IntentId::Work) {
                curIntent->abort();
                Actor::think(delta);
            }
            interacting = false;
        }

        if (inputManager.modifier()) {
            speed *= 3.1f;
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

            auto& map = std::dynamic_pointer_cast<GameScene>(Engine::instance().getScene())->getMap();
            if (map.collides(_sprite.getGlobalBounds())) {
                _sprite.move(-desiredVelocity);
            }
        }
    }
}

void Player::render(sf::RenderTarget& renderTarget) {
    Actor::render(renderTarget);

    if (drawHitbox) {
        setupHitbox();
        renderTarget.draw(hitbox);
    }
}

void Player::setupHitbox() {
    auto bounds = _sprite.getGlobalBounds();

    hitbox[0].position = sf::Vector2f(bounds.left, bounds.top);
    hitbox[1].position = sf::Vector2f(bounds.left + bounds.width, bounds.top);
    hitbox[2].position = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
    hitbox[3].position = sf::Vector2f(bounds.left, bounds.top + bounds.height);
    hitbox[4].position = sf::Vector2f(bounds.left, bounds.top);

    hitbox[0].color = sf::Color::Green;
    hitbox[1].color = sf::Color::Green;
    hitbox[2].color = sf::Color::Green;
    hitbox[3].color = sf::Color::Green;
    hitbox[4].color = sf::Color::Green;
}
