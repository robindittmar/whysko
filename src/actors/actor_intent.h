#ifndef WHYSKO_ACTOR_INTENT_H
#define WHYSKO_ACTOR_INTENT_H

#include <cstdint>


#define ACTOR_INTENT_UNDEFINED 0

class Actor;

enum class IntentProgress {
    InProgress,
    Complete,
    Error
};

class ActorIntent {
public:
    explicit ActorIntent(uint32_t intentId);
    virtual ~ActorIntent() = default;

    virtual void start(Actor& actor) = 0;
    virtual IntentProgress act(Actor& actor, float delta) = 0;

    inline uint32_t getId() const;
    inline void setId(int _id);

protected:
    uint32_t id = ACTOR_INTENT_UNDEFINED;
};


uint32_t ActorIntent::getId() const {
    return id;
}

void ActorIntent::setId(int _id) {
    id = _id;
}


#endif//WHYSKO_ACTOR_INTENT_H
