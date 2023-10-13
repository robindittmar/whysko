#ifndef WHYSKO_ENGINE_H
#define WHYSKO_ENGINE_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Clock.hpp"
#include <cassert>
#include <memory>
#include <random>
#include <utility>

#include "../scenes/scene.h"
#include "debug_view.h"
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
    void postRender();

    inline std::shared_ptr<Scene> getScene() const;
    inline void setScene(const std::shared_ptr<Scene>& s);

    inline ResourceManager& getResourceManager();

    inline float getRandomNumber();

    inline uint32_t getTickrate() const;
    inline void setTickrate(uint32_t ticks);

    inline uint32_t getFramerate() const;
    inline void setFramerate(uint32_t frames);

    inline DebugView& getDebugView();

private:
    Engine() = default;
    ~Engine() = default;


    uint32_t tickrate = 128;
    uint64_t ticktime = 1000000 / tickrate;
    uint64_t ticktimeAccumulator = 0;

    uint32_t framerate = 0;
    uint64_t frametime = 0;

    uint32_t ticksLastSecond = 0;
    uint32_t ticksCurrentSecond = 0;

    uint32_t framesLastSecond = 0;
    uint32_t framesCurrentSecond = 0;

    uint64_t lastFrameTime = 0;

    sf::Clock ticksClock;
    sf::Clock secondsClock;
    sf::Clock frameClock;

    sf::Clock startupClock;

    ResourceManager resourceManager;

    std::random_device randomDevice;
    std::default_random_engine randomEngine{randomDevice()};
    std::uniform_real_distribution<float> randomDistribution{0.0f, std::nextafter(1.0f, 2.0f)};

    DebugView debugView;
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

float Engine::getRandomNumber() {
    return randomDistribution(randomEngine);
}

uint32_t Engine::getTickrate() const {
    return tickrate;
}

void Engine::setTickrate(uint32_t ticks) {
    assert(ticks > 0);
    tickrate = ticks;
    ticktime = 1000000 / tickrate;
}

uint32_t Engine::getFramerate() const {
    return framerate;
}

void Engine::setFramerate(uint32_t frames) {
    framerate = frames;
    frametime = framerate > 0 ? 1000000 / framerate : 0;
}

DebugView& Engine::getDebugView() {
    return debugView;
}


#endif//WHYSKO_ENGINE_H
