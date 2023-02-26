#ifndef WHYSKO_INPUT_SETTINGS_H
#define WHYSKO_INPUT_SETTINGS_H

#include <SFML/Window/Keyboard.hpp>


class InputSettings {
public:
    static InputSettings& instance();

    sf::Keyboard::Key keyMoveUp = sf::Keyboard::Key::W;
    sf::Keyboard::Key keyMoveDown = sf::Keyboard::Key::S;
    sf::Keyboard::Key keyMoveLeft = sf::Keyboard::Key::A;
    sf::Keyboard::Key keyMoveRight = sf::Keyboard::Key::D;
    sf::Keyboard::Key keyInteract = sf::Keyboard::Key::Space;
    sf::Keyboard::Key keyMod = sf::Keyboard::Key::LShift;

private:
    InputSettings() = default;
    ~InputSettings() = default;
};


#endif//WHYSKO_INPUT_SETTINGS_H
