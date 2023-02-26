#include "move_intent.h"
#include "actor.h"
#include <cmath>

MoveIntent::MoveIntent(sf::Vector2f moveTo, float speed)
    : ActorIntent(IntentId::Move), target(moveTo), speed(speed) {}

void MoveIntent::start(Actor& actor) {
}

IntentProgress MoveIntent::act(Actor& actor, float delta) {
    if (aborted) {
        return IntentProgress::Complete;
    }

    IntentProgress rtn = IntentProgress::InProgress;

    float deltaX = (target.x - actor.sprite().getPosition().x);
    float deltaY = (target.y - actor.sprite().getPosition().y);

    float len = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (len < speed * delta) {
        len = speed;
        rtn = IntentProgress::Complete;
    }
    float moveX = ((deltaX / len) * speed) * delta;
    float moveY = ((deltaY / len) * speed) * delta;

    actor.sprite().move(moveX, moveY);
    return rtn;
}
