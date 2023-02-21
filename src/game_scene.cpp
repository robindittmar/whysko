#include "game_scene.h"


void GameScene::Setup() {
    const int level[] =
            {
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
            };

    map.Setup(sf::Vector2u(32, 32), level, 16, 8);
}

void GameScene::Think(float delta) {
    for (auto& actor : actors) {
        actor->Think(delta);
    }
}

void GameScene::Render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(map);

    for (const auto& actor : actors) {
        actor->Render(renderTarget);
    }
}

void GameScene::AddActor(const std::shared_ptr<Actor>& actor) {
    actors.push_back(actor);
}
