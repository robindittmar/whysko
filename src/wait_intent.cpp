#include "wait_intent.h"


WaitIntent::WaitIntent(float seconds)
    : secs(seconds) {}

void WaitIntent::Start(Actor& actor) {
    clock.restart();
}

IntentProgress WaitIntent::Act(Actor& actor) {
    float elapsed = clock.getElapsedTime().asSeconds();
    if (elapsed > secs) {
        return IntentProgress::Complete;
    } else {
        return IntentProgress::InProgress;
    }
}

