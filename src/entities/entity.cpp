#include "entity.h"

void Entity::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(sprite);
}
