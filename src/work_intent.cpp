#include "work_intent.h"
#include "actor.h"


WorkIntent::WorkIntent(float durationInSeconds)
    : durationInSeconds(durationInSeconds) {}

void WorkIntent::start(Actor& actor) {
    startingAngle = actor.sprite().getRotation();
    clock.restart();
}

IntentProgress WorkIntent::act(Actor& actor, float delta) {
    if (clock.getElapsedTime().asSeconds() > durationInSeconds) {
        actor.sprite().setRotation(startingAngle);
        return IntentProgress::Complete;
    }

    actor.sprite().rotate(25.0f * delta);
    return IntentProgress::InProgress;
}