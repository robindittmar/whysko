#ifndef WHYSKO_MOVE_INTENT_H
#define WHYSKO_MOVE_INTENT_H

#include "actor_intent.h"

#include <SFML/System/Vector2.hpp>


class MoveIntent : public ActorIntent {
public:
    MoveIntent(sf::Vector2f moveTo, float speed);

    MoveIntent(sf::Vector2<float> vector2);

    void Start(Actor& actor) override;
    IntentProgress Act(Actor& actor) override;
private:
    sf::Vector2f target;
    float speed;
};


#endif //WHYSKO_MOVE_INTENT_H