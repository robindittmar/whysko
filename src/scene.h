#ifndef WHYSKO_SCENE_H
#define WHYSKO_SCENE_H

#include <SFML/Graphics/RenderTarget.hpp>


class Scene {
public:
    virtual void Think(float delta) = 0;
    virtual void Render(sf::RenderTarget& renderTarget) = 0;
};


#endif //WHYSKO_SCENE_H
