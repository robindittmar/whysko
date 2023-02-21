#include "game_scene.h"
#include "map_loader.h"

void GameScene::setup() {
    MapLoader loader;
    loader.loadFromFile("map/0.json");
    loader.apply(map);
}

void GameScene::think(float delta) {
    for (auto& actor: actors) {
        actor->think(delta);
    }
}

void GameScene::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(map);

    for (const auto& actor: actors) {
        actor->render(renderTarget);
    }
}

void GameScene::addActor(const std::shared_ptr<Actor>& actor) {
    actors.push_back(actor);
}
