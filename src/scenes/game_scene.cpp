#include "game_scene.h"
#include "../world/map_builder.h"

void GameScene::setup() {
    map = MapBuilder()
              .loadFromFile("map/0.json")
              .setDrawDebugInfo(true)
              .build();
}

void GameScene::think(float deltaTime) {
    for (auto& entity : entities) {
        if (!entity->getActive())
            continue;

        entity->think(deltaTime);
    }

    entities.insert(entities.end(), entityQueue.begin(), entityQueue.end());
    entityQueue.clear();
}

void GameScene::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(map);

    for (const auto& entity : entities) {
        if (!entity->getActive())
            continue;

        entity->render(renderTarget);
    }
}

void GameScene::addEntity(const std::shared_ptr<Entity>& entity) {
    entity->setId(entityCounter++);
    entityQueue.push_back(entity);
}

void GameScene::removeInactiveEntities() {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](const auto& entity) {
                       return !entity->getActive();
                   }),
                   entities.end());
}
