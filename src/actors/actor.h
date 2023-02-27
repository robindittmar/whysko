#ifndef WHYSKO_ACTOR_H
#define WHYSKO_ACTOR_H

#include "actor_intent.h"

#include <memory>
#include <queue>

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"


enum class ActorState {
    Idle = 0,
    Acting
};

class Actor {
public:
    Actor() = default;
    virtual ~Actor() = default;

    virtual void think(float delta);
    virtual void render(sf::RenderTarget& renderTarget);

    void pushIntent(const std::shared_ptr<ActorIntent>& intent);
    void pushIntents(const std::vector<std::shared_ptr<ActorIntent>>& intents);

    inline ActorState getState() const;
    inline void setState(ActorState& s);

    inline sf::Sprite& sprite();

protected:
    virtual std::shared_ptr<ActorIntent> nextIntent();

    sf::Sprite _sprite;
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

sf::Sprite& Actor::sprite() {
    return _sprite;
}


#endif//WHYSKO_ACTOR_H
