#include "actor_intent.h"

ActorIntent::ActorIntent(IntentId intentId)
    : id(intentId) {}

void ActorIntent::abort() {
    aborted = true;
}
