#include "waiter.h"


Waiter::Waiter(uint32_t id, float x, float y, const std::string& texture)
    : id(id) {
    _sprite.setTexture(Engine::instance().getResourceManager().loadTexture(texture));
    _sprite.setOrigin(32.0f, 32.0f);
    _sprite.setPosition(x, y);
    _sprite.setScale(2.5f, 2.5f);
}
