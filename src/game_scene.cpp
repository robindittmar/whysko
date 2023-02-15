#include "game_scene.h"


void GameScene::Setup() {
    map.Setup();
}

void GameScene::Think() {
    for (auto& actor : actors) {
        actor->Think();
    }
}

void GameScene::Render(sf::RenderTarget& renderTarget) {
    map.Render(renderTarget);

    for (const auto& actor : actors) {
        actor->Render(renderTarget);
    }
}

void GameScene::AddActor(const std::shared_ptr<Actor>& actor) {
    actors.push_back(actor);
}
