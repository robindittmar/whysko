#include "player.h"
#include "../engine/player_settings.h"
#include "work_intent.h"

Player::Player() {
    _sprite.setTexture(Engine::instance().getResourceManager().loadTexture("img/cat2.png"));
    _sprite.setOrigin(32.0f, 32.0f);
    _sprite.setPosition(600.0f, 600.0f);
    _sprite.setScale(5.0f, 5.0f);
}

void Player::handleEvent(sf::Event& event) {
    PlayerSettings& settings = PlayerSettings::instance();

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == settings.keyMoveUp) {
            moveUpPressed = true;
        } else if (event.key.code == settings.keyMoveDown) {
            moveDownPressed = true;
        } else if (event.key.code == settings.keyMoveLeft) {
            moveLeftPressed = true;
        } else if (event.key.code == settings.keyMoveRight) {
            moveRightPressed = true;
        } else if (event.key.code == settings.keyInteract) {
            interactPressed = true;
        } else if (event.key.code == settings.keyMod) {
            modPressed = true;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == settings.keyMoveUp) {
            moveUpPressed = false;
        } else if (event.key.code == settings.keyMoveDown) {
            moveDownPressed = false;
        } else if (event.key.code == settings.keyMoveLeft) {
            moveLeftPressed = false;
        } else if (event.key.code == settings.keyMoveRight) {
            moveRightPressed = false;
        } else if (event.key.code == settings.keyInteract) {
            interactPressed = false;
        } else if (event.key.code == settings.keyMod) {
            modPressed = false;
        }
    }
}

void Player::think(float delta) {
    sf::Vector2f desiredVelocity = {0.f, 0.f};
    float speed = 170.0f;

    if (interactPressed) {
        if (curIntent && curIntent->getId() == ACTOR_INTENT_WORK) {
            Actor::think(delta);
        } else {
            pushIntent(std::make_shared<WorkIntent>(10.0f));
            Actor::think(delta);
        }

    } else {
        if (modPressed) {
            speed *= 1.7f;
        }
        if (moveUpPressed) {
            desiredVelocity.y -= speed;
        }
        if (moveDownPressed) {
            desiredVelocity.y += speed;
        }
        if (moveLeftPressed) {
            desiredVelocity.x -= speed;
        }
        if (moveRightPressed) {
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
