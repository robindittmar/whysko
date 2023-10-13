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

    if (inputManager.modifier()) {
        speed *= 3.1f;
    }
    if (inputManager.moveUp()) {
        desiredVelocity.y -= speed * deltaTime;
    }
    if (inputManager.moveDown()) {
        desiredVelocity.y += speed * deltaTime;
    }
    if (inputManager.moveLeft()) {
        desiredVelocity.x -= speed * deltaTime;
    }
    if (inputManager.moveRight()) {
        desiredVelocity.x += speed * deltaTime;
    }

    move(deltaTime, desiredVelocity);
    if (shootCooldown <= 0.0f) {
        if (inputManager.interact()) {
            shoot(deltaTime);
            shootCooldown = MAX_SHOOT_COOLDOWN;
        }
    } else {
        shootCooldown -= deltaTime;
    }
}

void Player::render(sf::RenderTarget& renderTarget) {
    Entity::render(renderTarget);

    if (drawHitbox) {
        setupHitbox();
        renderTarget.draw(hitbox);
    }
}

void Player::move(float deltaTime, sf::Vector2f desiredVelocity) {
    auto gameScene = std::dynamic_pointer_cast<GameScene>(Engine::instance().getScene());
    auto& collisionManager = gameScene->getCollisionManager();
    //    auto& map = gameScene->getMap();

    float len = sqrt(desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y);
    if (len > 0.f) {
        velocity.x = desiredVelocity.x * std::abs(desiredVelocity.x / len);
        velocity.y = desiredVelocity.y * std::abs(desiredVelocity.y / len);

        sprite.move(velocity);
        std::vector<sf::FloatRect> colliding;
        if (collisionManager.collidesWithMap(sprite.getGlobalBounds(), colliding)) {
            auto fixMove = collisionManager.fixMove(
                velocity,
                sprite.getGlobalBounds(),
                colliding);
            sprite.move(fixMove);

            if (fixMove.x != 0.0f) {
                velocity.x = 0.0f;
            }
            if (fixMove.y != 0.0f) {
                velocity.y = 0.0f;
            }
        }
    } else {
        if (velocity.x != 0.0f || velocity.y != 0.0f) {
            velocity.x /= 2;
            velocity.y /= 2;
            if (velocity.x <= 0.002f && velocity.y <= 0.002f) {
                velocity.x = 0.f;
                velocity.y = 0.f;
            }
        }
    }
}

void Player::shoot(float deltaTime) {
    auto gameScene = std::dynamic_pointer_cast<GameScene>(Engine::instance().getScene());

    for (int i = 0; i < 12; i++) {
        float bulletSpeed = 3500.0f + ((Engine::instance().getRandomNumber() - 0.5f) * 300.f);
        float spread = (Engine::instance().getRandomNumber() - 0.5f) * 2.0f * 3.14159f;

        sf::Vector2f aimingAt = InputManager::instance().mousePosWorld();

        // Figure out shoot direction
        sf::Vector2f bulletVelocity = aimingAt - sprite.getPosition();
        float len = sqrt(bulletVelocity.x * bulletVelocity.x + bulletVelocity.y * bulletVelocity.y);
        bulletVelocity /= len;

        // Add spread
        float acosi = acos(bulletVelocity.x) + spread;
        float asini = asin(bulletVelocity.y) + spread;

        bulletVelocity.x = cos(acosi);
        bulletVelocity.y = sin(asini);

        // Multiply with speed
        bulletVelocity *= bulletSpeed * deltaTime;

        // Add player velocity to bullet
        bulletVelocity += velocity;

        gameScene->addEntity(std::make_shared<Bullet>(sprite.getPosition(), bulletVelocity));
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
