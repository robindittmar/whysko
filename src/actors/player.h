#ifndef WHYSKO_PLAYER_H
#define WHYSKO_PLAYER_H

#include "actor.h"


class Player : public Actor {
public:
    Player();
    ~Player() override = default;

    void think(float delta) override;

private:
    bool interacting = false;
};


#endif//WHYSKO_PLAYER_H
