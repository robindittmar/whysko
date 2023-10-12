#include "actor.h"

void Actor::think(float deltaTime) {
    if (state == ActorState::Idle) {
        curIntent = this->nextIntent();
        if (curIntent) {
            curIntent->start(*this);
            state = ActorState::Acting;
        }
    }

    if (state == ActorState::Acting) {
        if (curIntent->act(*this, deltaTime) == IntentProgress::Complete) {
            state = ActorState::Idle;
            curIntent = nullptr;
        }
    }
}

void Actor::pushIntent(const std::shared_ptr<ActorIntent>& intent) {
    intentQueue.push(intent);
}

void Actor::pushIntents(const std::vector<std::shared_ptr<ActorIntent>>& intents) {
    for (auto& intent : intents) {
        pushIntent(intent);
    }
}

std::shared_ptr<ActorIntent> Actor::nextIntent() {
    if (intentQueue.empty()) {
        return nullptr;
    }

    auto intent = intentQueue.front();
    intentQueue.pop();

    return intent;
}
