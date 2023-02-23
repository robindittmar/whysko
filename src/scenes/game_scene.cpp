#include "game_scene.h"
#include "../world/map_builder.h"

void GameScene::setup() {
    map = MapBuilder()
              .loadFromFile("map/0.json")
              .build();
}

void GameScene::think(float delta) {
    for (auto& actor : actors) {
        actor->think(delta);
    }
}

void GameScene::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(map);

    for (const auto& actor : actors) {
        actor->render(renderTarget);
    }
}

void GameScene::addActor(const std::shared_ptr<Actor>& actor) {
    actors.push_back(actor);
}
