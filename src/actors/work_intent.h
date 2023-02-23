#ifndef WHYSKO_WORK_INTENT_H
#define WHYSKO_WORK_INTENT_H

#include "actor_intent.h"

#include "SFML/System/Clock.hpp"

#define ACTOR_INTENT_WORK 12


class WorkIntent : public ActorIntent {
public:
    explicit WorkIntent(float durationInSeconds);

    void start(Actor& actor) override;
    IntentProgress act(Actor& actor, float delta) override;

private:
    float startingAngle;
    float durationInSeconds;
    sf::Clock clock;
};


#endif//WHYSKO_WORK_INTENT_H
