#include "engine.h"

#include "logging.h"
#include "settings_repository.h"

#include <random>
#include <sstream>

#include "SFML/System.hpp"


Engine& Engine::instance() {
    static Engine e;
    return e;
}

bool Engine::initialize() {
    bool rtn = true;

    debugView.init();
    debugView.addDynamicValue("framerate", &framesLastSecond);
    debugView.addDynamicValue("tickrate", &ticksLastSecond);

    rtn = rtn & SettingsRepository::loadInputSettings();

    return rtn;
}

bool Engine::shutdown() {
    bool rtn = true;

    rtn = rtn & SettingsRepository::writeInputSettings();
    return rtn;
}

void Engine::think() {
    ticktimeAccumulator += frameClock.restart().asMicroseconds();


    while (ticktimeAccumulator > ticktime) {
        Engine::tick((float)ticktime / 1000000.f);
        ticksCurrentSecond++;

        ticktimeAccumulator -= ticktime;
    }

    if (secondsClock.getElapsedTime().asMicroseconds() > 1000000) {
        ticksLastSecond = ticksCurrentSecond;
        ticksCurrentSecond = 0;

        framesLastSecond = framesCurrentSecond;
        framesCurrentSecond = 0;

        secondsClock.restart();
    }
}

void Engine::tick(float delta) {
    if (scene) {
        scene->think(delta);
    }
}

void Engine::render(sf::RenderTarget& renderTarget) {
    if (scene) {
        scene->render(renderTarget);
    }

    debugView.render(renderTarget);
}

void Engine::postRender() {
    lastFrameTime = frameClock.getElapsedTime().asMicroseconds();
    if (framerate > 0) {
        // super simple, but works good enough
        if (lastFrameTime < frametime) {
            sf::sleep(sf::microseconds(frametime - lastFrameTime - 100));
        }
    }

    framesCurrentSecond++;
}
