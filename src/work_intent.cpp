#include "work_intent.h"
#include "actor.h"


WorkIntent::WorkIntent(float durationInSeconds)
    : durationInSeconds(durationInSeconds) {}

void WorkIntent::Start(Actor& actor) {
    startingAngle = actor.Sprite().getRotation();
    clock.restart();
}

IntentProgress WorkIntent::Act(Actor& actor, float delta) {
    if (clock.getElapsedTime().asSeconds() > durationInSeconds) {
        actor.Sprite().setRotation(startingAngle);
        return IntentProgress::Complete;
    }

    actor.Sprite().rotate(25.0f * delta);
    return IntentProgress::InProgress;
}