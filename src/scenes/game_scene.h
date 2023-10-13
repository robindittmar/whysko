#ifndef WHYSKO_GAME_SCENE_H
#define WHYSKO_GAME_SCENE_H

#include <memory>
#include <vector>

#include "../engine/collision_manager.h"
#include "../entities/entity.h"
#include "../world/map.h"
#include "scene.h"


class GameScene : public Scene {
public:
    GameScene();

    void setup();

    void think(float deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

    void addEntity(const std::shared_ptr<Entity>& entity);

    inline std::vector<std::shared_ptr<Entity>>& getEntities();
    inline Map& getMap();

    inline CollisionManager& getCollisionManager();

private:
    uint32_t entityCount = 0;
    uint64_t entityIdCounter = 0;
    Map map;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> entityQueue;

    CollisionManager collisionManager;
};


std::vector<std::shared_ptr<Entity>>& GameScene::getEntities() {
    return entities;
}

Map& GameScene::getMap() {
    return map;
}

CollisionManager& GameScene::getCollisionManager() {
    return collisionManager;
}

#endif//WHYSKO_GAME_SCENE_H
