#ifndef WHYSKO_GAME_SCENE_H
#define WHYSKO_GAME_SCENE_H

#include <memory>
#include <vector>

#include "../entities/entity.h"
#include "../world/map.h"
#include "scene.h"


class GameScene : public Scene {
public:
    void setup();

    void think(float deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;

    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeInactiveEntities();

    inline Map& getMap();

private:
    uint32_t entityCount = 0;
    uint64_t entityIdCounter = 0;
    Map map;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> entityQueue;
};


Map& GameScene::getMap() {
    return map;
}

#endif//WHYSKO_GAME_SCENE_H
