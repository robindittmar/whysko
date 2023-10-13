#ifndef WHYSKO_INPUT_MANAGER_H
#define WHYSKO_INPUT_MANAGER_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"


class InputManager {
public:
    static InputManager& instance();

    void init(sf::RenderWindow* renderWindow);
    void handleEvent(sf::Event& event);

    inline sf::Vector2f mousePosWorld() const;

    inline bool moveUp() const;
    inline bool moveDown() const;
    inline bool moveLeft() const;
    inline bool moveRight() const;
    inline bool interact() const;
    inline bool modifier() const;

private:
    InputManager() = default;
    ~InputManager() = default;

    sf::RenderWindow* window = nullptr;

    sf::Vector2f mousePosWorldVec = sf::Vector2f(0.0f, 0.0f);

    bool moveUpPressed = false;
    bool moveDownPressed = false;
    bool moveLeftPressed = false;
    bool moveRightPressed = false;
    bool interactPressed = false;
    bool modPressed = false;
};


sf::Vector2f InputManager::mousePosWorld() const {
    return mousePosWorldVec;
}

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
