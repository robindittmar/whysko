#ifndef WHYSKO_ENGINE_H
#define WHYSKO_ENGINE_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <utility>

#include "scene.h"
#include "resource_manager.h"

class Engine {
public:
    Engine(Engine&) = delete;
    Engine(Engine&&) = delete;

    static Engine& Instance();

    bool Initialize();
    bool Shutdown();

    void Think();
    void Tick(float delta);
    void Render(sf::RenderTarget& renderTarget);

    inline std::shared_ptr<Scene> GetScene() const;
    inline void SetScene(const std::shared_ptr<Scene>& s);

    inline ResourceManager& GetResourceManager();

    inline uint32_t GetTickrate() const;
    inline void SetTickrate(uint32_t ticks);

    inline bool GetDrawDebugString() const;
    inline void SetDrawDebugString(bool draw);
private:
    Engine() = default;
    ~Engine() = default;


    void DrawDebugString(sf::RenderTarget& target) const;

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

    bool drawDebugString = false;

    sf::Clock startupClock;

    ResourceManager resourceManager;

    sf::Font& renderFont = resourceManager.LoadFont("fnt/FiraCode-Regular.ttf");

    std::shared_ptr<Scene> scene = nullptr;
};


std::shared_ptr<Scene> Engine::GetScene() const {
    return scene;
}

void Engine::SetScene(const std::shared_ptr<Scene>& s) {
    scene = s;
}

ResourceManager& Engine::GetResourceManager() {
    return resourceManager;
}

uint32_t Engine::GetTickrate() const {
    return tickrate;
}

void Engine::SetTickrate(const uint32_t ticks) {
    tickrate = ticks;
    ticktime = 1000000 / tickrate;
}

bool Engine::GetDrawDebugString() const {
    return drawDebugString;
}

void Engine::SetDrawDebugString(const bool draw) {
    drawDebugString = draw;
}


#endif //WHYSKO_ENGINE_H
