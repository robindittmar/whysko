#ifndef WHYSKO_PLAYER_H
#define WHYSKO_PLAYER_H

#include "../engine/engine.h"
#include "SFML/Window/Event.hpp"
#include "actor.h"


class Player : public Actor {
public:
    Player();
    ~Player() override = default;

    void handleEvent(sf::Event& event);

    void think(float delta) override;

private:
    bool moveUpPressed = false;
    bool moveDownPressed = false;
    bool moveLeftPressed = false;
    bool moveRightPressed = false;
    bool interactPressed = false;
    bool modPressed = false;
};


#endif//WHYSKO_PLAYER_H
