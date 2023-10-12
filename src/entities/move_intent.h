#ifndef WHYSKO_MOVE_INTENT_H
#define WHYSKO_MOVE_INTENT_H

#include "actor_intent.h"

#include "SFML/System/Vector2.hpp"


class MoveIntent : public ActorIntent {
public:
    MoveIntent(sf::Vector2f moveTo, float speed);

    void start(Actor& actor) override;
    IntentProgress act(Actor& actor, float deltaTime) override;

private:
    sf::Vector2f target;
    float speed;
};


#endif//WHYSKO_MOVE_INTENT_H
