#ifndef WHYSKO_ACTOR_H
#define WHYSKO_ACTOR_H

#include "actor_intent.h"

#include <memory>
#include <queue>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>


enum class ActorState {
    Idle = 0,
    Acting
};

class Actor {
public:
    Actor() = default;
    virtual ~Actor() = default;

    virtual void Think(float delta);
    virtual void Render(sf::RenderTarget& renderTarget) const;

    void PushIntent(const std::shared_ptr<ActorIntent>& intent);
    void PushIntents(const std::vector<std::shared_ptr<ActorIntent>>& intents);

    inline ActorState GetState() const;
    inline void SetState(ActorState& s);

    inline sf::Sprite& Sprite();
protected:
    virtual std::shared_ptr<ActorIntent> NextIntent();

    sf::Sprite sprite;
    ActorState state = ActorState::Idle;
    std::shared_ptr<ActorIntent> curIntent;
    std::queue<std::shared_ptr<ActorIntent>> intentQueue;

    friend class ActorIntent;
};


ActorState Actor::GetState() const {
    return state;
}

void Actor::SetState(ActorState& s) {
    state = s;
}

sf::Sprite& Actor::Sprite() {
    return sprite;
}


#endif //WHYSKO_ACTOR_H
