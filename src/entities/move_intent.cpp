#include "move_intent.h"
#include "actor.h"
#include <cmath>

MoveIntent::MoveIntent(sf::Vector2f moveTo, float speed)
    : ActorIntent(IntentId::Move), target(moveTo), speed(speed) {}

void MoveIntent::start(Actor& actor) {
}

IntentProgress MoveIntent::act(Actor& actor, float deltaTime) {
    if (aborted) {
        return IntentProgress::Complete;
    }

    IntentProgress rtn = IntentProgress::InProgress;

    float deltaX = (target.x - actor.getSprite().getPosition().x);
    float deltaY = (target.y - actor.getSprite().getPosition().y);

    float len = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (len < speed * deltaTime) {
        len = speed;
        rtn = IntentProgress::Complete;
    }
    float moveX = ((deltaX / len) * speed) * deltaTime;
    float moveY = ((deltaY / len) * speed) * deltaTime;

    actor.getSprite().move(moveX, moveY);
    return rtn;
}
