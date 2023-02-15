#include "actor.h"

void Actor::Think() {
    if (state == ActorState::Idle) {
        curIntent = this->NextIntent();
        if (curIntent) {
            curIntent->Start(*this);
            state = ActorState::Acting;
        }
    }

    if (state == ActorState::Acting) {
        if (curIntent->Act(*this) == IntentProgress::Complete) {
            state = ActorState::Idle;
            curIntent = nullptr;
        }
    }
}

void Actor::Render(sf::RenderTarget& renderTarget) const {
    renderTarget.draw(sprite);
}

void Actor::PushIntent(const std::shared_ptr<ActorIntent>& intent) {
    intentQueue.push(intent);
}

void Actor::PushIntents(const std::vector<std::shared_ptr<ActorIntent>>& intents) {
    for (auto& intent : intents) {
        PushIntent(intent);
    }
}

std::shared_ptr<ActorIntent> Actor::NextIntent() {
    if (intentQueue.empty()) {
        return nullptr;
    }

    auto intent = intentQueue.front();
    intentQueue.pop();

    return intent;
}
