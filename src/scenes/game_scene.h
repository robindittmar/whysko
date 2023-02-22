#ifndef WHYSKO_GAME_SCENE_H
#define WHYSKO_GAME_SCENE_H

#include <memory>
#include <vector>

#include "../actors/actor.h"
#include "../world/map.h"
#include "scene.h"


class GameScene : public Scene {
public:
    void setup();

    void think(float delta) override;
    void render(sf::RenderTarget& renderTarget) override;

    void addActor(const std::shared_ptr<Actor>& actor);

private:
    Map map;
    std::vector<std::shared_ptr<Actor>> actors;
};


#endif//WHYSKO_GAME_SCENE_H
