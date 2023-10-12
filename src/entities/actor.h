#ifndef WHYSKO_ACTOR_H
#define WHYSKO_ACTOR_H

#include "actor_intent.h"
#include "entity.h"

#include <memory>
#include <queue>

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"


enum class ActorState {
    Idle = 0,
    Acting
};

class Actor : public Entity {
public:
    Actor() = default;
    virtual ~Actor() = default;

    virtual void think(float deltaTime) override;

    void pushIntent(const std::shared_ptr<ActorIntent>& intent);
    void pushIntents(const std::vector<std::shared_ptr<ActorIntent>>& intents);

    inline ActorState getState() const;
    inline void setState(ActorState& s);

protected:
    virtual std::shared_ptr<ActorIntent> nextIntent();

    ActorState state = ActorState::Idle;
    std::shared_ptr<ActorIntent> curIntent;
    std::queue<std::shared_ptr<ActorIntent>> intentQueue;

    friend class ActorIntent;
};


ActorState Actor::getState() const {
    return state;
}

void Actor::setState(ActorState& s) {
    state = s;
}


#endif//WHYSKO_ACTOR_H
