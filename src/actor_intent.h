#ifndef WHYSKO_ACTOR_INTENT_H
#define WHYSKO_ACTOR_INTENT_H

#include <cstdint>


#define ACTOR_INTENT_UNDEFINED  0

class Actor;

enum class IntentProgress {
    InProgress,
    Complete,
    Error
};

class ActorIntent {
public:
    virtual void Start(Actor& actor) = 0;
    virtual IntentProgress Act(Actor& actor, float delta) = 0;

    inline uint32_t GetId() const;
    inline void SetId(int _id);
protected:
    uint32_t id = ACTOR_INTENT_UNDEFINED;
};


uint32_t ActorIntent::GetId() const {
    return id;
}

void ActorIntent::SetId(int _id) {
    id = _id;
}


#endif //WHYSKO_ACTOR_INTENT_H
