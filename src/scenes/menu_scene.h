#ifndef WHYSKO_MENU_SCENE_H
#define WHYSKO_MENU_SCENE_H

#include "scene.h"


class MenuScene : public Scene {
public:
    void think(float delta) override;
    void render(sf::RenderTarget& renderTarget) override;
    
private:
};


#endif//WHYSKO_MENU_SCENE_H
