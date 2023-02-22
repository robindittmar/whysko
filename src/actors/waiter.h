#ifndef WHYSKO_WAITER_H
#define WHYSKO_WAITER_H

#include "SFML/Graphics/Sprite.hpp"

#include "../engine/engine.h"
#include "actor.h"


class Waiter : public Actor {
public:
    Waiter(uint32_t id, float x, float y, const std::string& texture);
    ~Waiter() override = default;

private:
    uint32_t id;
};


#endif//WHYSKO_WAITER_H
