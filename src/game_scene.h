#ifndef WHYSKO_GAME_SCENE_H
#define WHYSKO_GAME_SCENE_H

#include <vector>
#include <memory>

#include "scene.h"
#include "map.h"
#include "actor.h"


class GameScene : public Scene {
public:
    void Setup();

    void Think() override;
    void Render(sf::RenderTarget& renderTarget) override;

    void AddActor(const std::shared_ptr<Actor>& actor);
private:
    Map map;
    std::vector<std::shared_ptr<Actor>> actors;
};


#endif //WHYSKO_GAME_SCENE_H
