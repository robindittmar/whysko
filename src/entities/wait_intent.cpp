#include "wait_intent.h"


WaitIntent::WaitIntent(float seconds)
    : ActorIntent(IntentId::Wait), secs(seconds) {}

void WaitIntent::start(Actor& actor) {
    clock.restart();
}

IntentProgress WaitIntent::act(Actor& actor, float deltaTime) {
    if (aborted) {
        return IntentProgress::Complete;
    }

    float elapsed = clock.getElapsedTime().asSeconds();
    if (elapsed > secs) {
        return IntentProgress::Complete;
    } else {
        return IntentProgress::InProgress;
    }
}
