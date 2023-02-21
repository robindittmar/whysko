#include "move_intent.h"
#include "actor.h"
#include <cmath>

MoveIntent::MoveIntent(sf::Vector2f moveTo, float speed)
    : target(moveTo)
    , speed(speed) {}

void MoveIntent::Start(Actor& actor) {

}

IntentProgress MoveIntent::Act(Actor& actor, float delta) {
    IntentProgress rtn = IntentProgress::InProgress;

    float deltaX = (target.x - actor.Sprite().getPosition().x);
    float deltaY = (target.y - actor.Sprite().getPosition().y);

    float len = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (len < speed * delta) {
        len = speed;
        rtn = IntentProgress::Complete;
    }
    float moveX = ((deltaX / len) * speed) * delta;
    float moveY = ((deltaY / len) * speed) * delta;

    actor.Sprite().move(moveX, moveY);
    return rtn;
}

