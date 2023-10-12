#ifndef WHYSKO_WAIT_INTENT_H
#define WHYSKO_WAIT_INTENT_H

#include "actor_intent.h"

#include "SFML/System/Clock.hpp"


class WaitIntent : public ActorIntent {
public:
    explicit WaitIntent(float seconds);

    void start(Actor& actor) override;
    IntentProgress act(Actor& actor, float deltaTime) override;

private:
    float secs;
    sf::Clock clock;
};


#endif//WHYSKO_WAIT_INTENT_H
