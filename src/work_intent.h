#ifndef WHYSKO_WORK_INTENT_H
#define WHYSKO_WORK_INTENT_H

#include "actor_intent.h"

#include "SFML/System/Clock.hpp"


class WorkIntent : public ActorIntent {
public:
    WorkIntent(float durationInSeconds);

    void Start(Actor& actor) override;
    IntentProgress Act(Actor& actor, float delta) override;
private:
    float startingAngle;
    float durationInSeconds;
    sf::Clock clock;
};


#endif //WHYSKO_WORK_INTENT_H
