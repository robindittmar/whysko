#include "game_scene.h"
#include "../world/map_builder.h"

void GameScene::setup() {
    map = MapBuilder()
              .loadFromFile("map/0.json")
              .setDrawDebugInfo(true)
              .build();

    Engine::instance().getDebugView().addDynamicValue("entity count", &entityCount);
}

void GameScene::think(float deltaTime) {
    bool cleanupEntities = false;
    for (auto& entity : entities) {
        if (!entity->getActive()) {
            cleanupEntities = true;
            continue;
        }

        entity->think(deltaTime);
    }

    if (cleanupEntities) {
        entities.erase(std::remove_if(entities.begin(), entities.end(), [](auto& e) {
                           return e->getActive() == false;
                       }),
                       entities.end());

        entityCount = entities.size();
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
    entity->setId(entityIdCounter++);
    entityQueue.push_back(entity);
    entityCount++;
}
