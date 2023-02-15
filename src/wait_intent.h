#ifndef WHYSKO_WAIT_INTENT_H
#define WHYSKO_WAIT_INTENT_H

#include "actor_intent.h"

#include "SFML/System/Clock.hpp"


class WaitIntent : public ActorIntent {
public:
    WaitIntent(float seconds);

    void Start(Actor& actor) override;
    IntentProgress Act(Actor& actor) override;
private:
    float secs;
    sf::Clock clock;
};


#endif //WHYSKO_WAIT_INTENT_H
