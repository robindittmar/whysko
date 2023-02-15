#include "move_intent.h"
#include "actor.h"
#include <cmath>

MoveIntent::MoveIntent(sf::Vector2f moveTo, float speed)
    : target(moveTo)
    , speed(speed) {}

void MoveIntent::Start(Actor& actor) {

}

IntentProgress MoveIntent::Act(Actor& actor) {
    IntentProgress rtn = IntentProgress::InProgress;

    float deltaX = target.x - actor.Sprite().getPosition().x;
    float deltaY = target.y - actor.Sprite().getPosition().y;

    float len = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (len < speed) {
        len = speed;
        rtn = IntentProgress::Complete;
    }
    float moveX = (deltaX / len) * speed;
    float moveY = (deltaY / len) * speed;

    actor.Sprite().move(moveX, moveY);
    return rtn;
}

