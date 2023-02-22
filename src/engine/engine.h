#ifndef WHYSKO_ENGINE_H
#define WHYSKO_ENGINE_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Clock.hpp"
#include <utility>

#include "../scenes/scene.h"
#include "resource_manager.h"

class Engine {
public:
    Engine(Engine&) = delete;
    Engine(Engine&&) = delete;

    static Engine& instance();

    bool initialize();
    bool shutdown();

    void think();
    void tick(float delta);
    void render(sf::RenderTarget& renderTarget);

    inline std::shared_ptr<Scene> getScene() const;
    inline void setScene(const std::shared_ptr<Scene>& s);

    inline ResourceManager& getResourceManager();

    inline uint32_t getTickrate() const;
    inline void setTickrate(uint32_t ticks);

    inline bool getDrawDebugString() const;
    inline void setDrawDebugString(bool draw);

private:
    Engine() = default;
    ~Engine() = default;


    void drawDebugString(sf::RenderTarget& target) const;

    uint32_t tickrate = 128;
    uint64_t ticktime = 1000000 / tickrate;
    uint64_t ticktimeAccumulator = 0;

    uint32_t ticksLastSecond = 0;
    uint32_t ticksCurrentSecond = 0;

    uint32_t framesLastSecond = 0;
    uint32_t framesCurrentSecond = 0;

    uint64_t lastFrameTime = 0;

    sf::Clock ticksClock;
    sf::Clock secondsClock;
    sf::Clock frameClock;

    bool _drawDebugString = false;

    sf::Clock startupClock;

    ResourceManager resourceManager;

    sf::Font& renderFont = resourceManager.loadFont("fnt/FiraCode-Regular.ttf");

    std::shared_ptr<Scene> scene = nullptr;
};


std::shared_ptr<Scene> Engine::getScene() const {
    return scene;
}

void Engine::setScene(const std::shared_ptr<Scene>& s) {
    scene = s;
}

ResourceManager& Engine::getResourceManager() {
    return resourceManager;
}

uint32_t Engine::getTickrate() const {
    return tickrate;
}

void Engine::setTickrate(uint32_t ticks) {
    tickrate = ticks;
    ticktime = 1000000 / tickrate;
}

bool Engine::getDrawDebugString() const {
    return _drawDebugString;
}

void Engine::setDrawDebugString(const bool draw) {
    _drawDebugString = draw;
}


#endif//WHYSKO_ENGINE_H
