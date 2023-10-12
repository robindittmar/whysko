#include "waiter.h"


Waiter::Waiter(uint32_t id, float x, float y, const std::string& texture)
    : id(id) {
    sprite.setTexture(Engine::instance().getResourceManager().loadTexture(texture));
    sprite.setOrigin(32.0f, 32.0f);
    sprite.setPosition(x, y);
    sprite.setScale(2.5f, 2.5f);
}
