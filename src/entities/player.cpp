#include "player.h"
#include "../engine/engine.h"
#include "../engine/input_manager.h"
#include "../scenes/game_scene.h"
#include "bullet.h"
#include "work_intent.h"
#include <cmath>

Player::Player() {
    sprite.setTexture(Engine::instance().getResourceManager().loadTexture("img/cat2.png"));
    sprite.setOrigin(32.0f, 32.0f);
    sprite.setPosition(600.0f, 600.0f);
    sprite.setScale(5.0f, 5.0f);

    hitbox.resize(5);
    hitbox.setPrimitiveType(sf::LineStrip);
}

void Player::think(float deltaTime) {
    sf::Vector2f desiredVelocity = {0.f, 0.f};
    float speed = 250.0f;
    auto& inputManager = InputManager::instance();
    auto gameScene = std::dynamic_pointer_cast<GameScene>(Engine::instance().getScene());
    auto& map = gameScene->getMap();

    //    if (inputManager.interact()) {
    //        if (curIntent && curIntent->getId() == IntentId::Work) {
    //            Actor::think(deltaTime);
    //        } else {
    //            interacting = true;
    //            pushIntent(std::make_shared<WorkIntent>(10.0f));
    //            Actor::think(deltaTime);
    //        }
    //
    //    } else {
    //        if (interacting) {
    //            if (curIntent && curIntent->getId() == IntentId::Work) {
    //                curIntent->abort();
    //                Actor::think(deltaTime);
    //            }
    //            interacting = false;
    //        }

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

    sf::Vector2f actualVelocity;
    float len = sqrt(desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y);
    if (len > 0) {
        actualVelocity.x = desiredVelocity.x * std::abs(desiredVelocity.x / len);
        actualVelocity.y = desiredVelocity.y * std::abs(desiredVelocity.y / len);
        float velocityX = actualVelocity.x * deltaTime;
        float velocityY = actualVelocity.y * deltaTime;

        sprite.move(velocityX, 0.f);
        if (map.collides(sprite.getGlobalBounds())) {
            actualVelocity.x = 0.0f;
            sprite.move(-velocityX, 0.f);
        }

        sprite.move(0.f, velocityY);
        if (map.collides(sprite.getGlobalBounds())) {
            actualVelocity.y = 0.0f;
            sprite.move(0.f, -velocityY);
        }
    }

    if (inputManager.interact()) {
        sf::Vector2f vel = actualVelocity + sf::Vector2f(1000.f, 0.f);
        std::shared_ptr<Bullet>
            b = std::make_shared<Bullet>(sprite.getPosition(), vel);
        gameScene->addEntity(b);
    }
    //    }
}

void Player::render(sf::RenderTarget& renderTarget) {
    Actor::render(renderTarget);

    if (drawHitbox) {
        setupHitbox();
        renderTarget.draw(hitbox);
    }
}

void Player::setupHitbox() {
    auto bounds = sprite.getGlobalBounds();

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
