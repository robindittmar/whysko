#include "input_manager.h"
#include "input_settings.h"

InputManager& InputManager::instance() {
    static InputManager im;
    return im;
}

void InputManager::init(sf::RenderWindow* renderWindow) {
    window = renderWindow;
}

void InputManager::handleEvent(sf::Event& event) {
    InputSettings& settings = InputSettings::instance();

    if (event.type == sf::Event::MouseMoved) {
        mousePosWorldVec = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
    } else if (event.type == sf::Event::KeyPressed) {
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
