#include "wait_intent.h"


WaitIntent::WaitIntent(float seconds)
    : ActorIntent(ACTOR_INTENT_WAIT), secs(seconds) {}

void WaitIntent::start(Actor& actor) {
    clock.restart();
}

IntentProgress WaitIntent::act(Actor& actor, float delta) {
    float elapsed = clock.getElapsedTime().asSeconds();
    if (elapsed > secs) {
        return IntentProgress::Complete;
    } else {
        return IntentProgress::InProgress;
    }
}
