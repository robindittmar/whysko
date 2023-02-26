#ifndef WHYSKO_INPUT_MANAGER_H
#define WHYSKO_INPUT_MANAGER_H

#include "SFML/Window/Event.hpp"


class InputManager {
public:
    static InputManager& instance();

    void handleEvent(sf::Event& event);

    inline bool moveUp() const;
    inline bool moveDown() const;
    inline bool moveLeft() const;
    inline bool moveRight() const;
    inline bool interact() const;
    inline bool modifier() const;

private:
    InputManager() = default;
    ~InputManager() = default;

    bool moveUpPressed = false;
    bool moveDownPressed = false;
    bool moveLeftPressed = false;
    bool moveRightPressed = false;
    bool interactPressed = false;
    bool modPressed = false;
};


bool InputManager::moveUp() const {
    return moveUpPressed;
}

bool InputManager::moveDown() const {
    return moveDownPressed;
}

bool InputManager::moveLeft() const {
    return moveLeftPressed;
}

bool InputManager::moveRight() const {
    return moveRightPressed;
}

bool InputManager::interact() const {
    return interactPressed;
}

bool InputManager::modifier() const {
    return modPressed;
}


#endif//WHYSKO_INPUT_MANAGER_H
