#include "engine.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System.hpp"

#include "logging.h"
#include <sstream>

Engine& Engine::instance() {
    static Engine e;
    return e;
}

bool Engine::initialize() {
    return true;
}

bool Engine::shutdown() {
    return true;
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

    Engine::drawDebugString(renderTarget);
}

void Engine::postRender() {
    lastFrameTime = frameClock.getElapsedTime().asMicroseconds();
    if (framerate > 0) {
        // super simple, but works good enough
        if (lastFrameTime < frametime) {
            sf::sleep(sf::microseconds(frametime - lastFrameTime));
        }
    }

    framesCurrentSecond++;
}

void Engine::drawDebugString(sf::RenderTarget& target) const {
    if (_drawDebugString) {
        sf::Text text(std::string("fps: ") +
                          std::to_string(framesLastSecond) +
                          std::string(" / tickrate: ") +
                          std::to_string(ticksLastSecond),
                      renderFont, 16);

        text.setPosition(0.0f, 0.0f);

        auto view = target.getView();
        auto debugView = sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
        target.setView(debugView);
        target.draw(text);
        target.setView(view);
    }
}
