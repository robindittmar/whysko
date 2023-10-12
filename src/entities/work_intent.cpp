#include "work_intent.h"
#include "actor.h"


WorkIntent::WorkIntent(float durationInSeconds)
    : ActorIntent(IntentId::Work), durationInSeconds(durationInSeconds), startingAngle(0.0f) {}

void WorkIntent::start(Actor& actor) {
    startingAngle = actor.getSprite().getRotation();
    clock.restart();
}

IntentProgress WorkIntent::act(Actor& actor, float deltaTime) {
    if (aborted || clock.getElapsedTime().asSeconds() > durationInSeconds) {
        actor.getSprite().setRotation(startingAngle);
        return IntentProgress::Complete;
    }

    actor.getSprite().rotate(25.0f * deltaTime);
    return IntentProgress::InProgress;
}
