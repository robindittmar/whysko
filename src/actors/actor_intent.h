#ifndef WHYSKO_ACTOR_INTENT_H
#define WHYSKO_ACTOR_INTENT_H

#include "intent_id.h"


class Actor;

enum class IntentProgress {
    InProgress,
    Complete,
    Error
};

class ActorIntent {
public:
    explicit ActorIntent(IntentId intentId);
    virtual ~ActorIntent() = default;

    virtual void start(Actor& actor) = 0;
    virtual IntentProgress act(Actor& actor, float delta) = 0;

    inline IntentId getId() const;
    inline void setId(IntentId _id);

protected:
    IntentId id = IntentId::Undefined;
};


IntentId ActorIntent::getId() const {
    return id;
}

void ActorIntent::setId(IntentId _id) {
    id = _id;
}


#endif//WHYSKO_ACTOR_INTENT_H
