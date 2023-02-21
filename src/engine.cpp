#include "engine.h"
#include "SFML/Graphics/Text.hpp"

#include <sstream>
#include "logging.h"

Engine& Engine::Instance() {
    static Engine e;
    return e;
}

bool Engine::Initialize() {
    return true;
}

bool Engine::Shutdown() {
    return true;
}

void Engine::Think() {
    ticktimeAccumulator += frameClock.restart().asMicroseconds();

    while (ticktimeAccumulator > ticktime) {
        Engine::Tick((float)ticktime / 1000000.f);
        ticksCurrentSecond++;

        ticktimeAccumulator -= ticktime;
    }
//    uint32_t ticksToRun = (ticksClock.getElapsedTime().asMicroseconds()) / (1000000 / tickrate);
//    if (ticksToRun > 0) {
//        for (uint32_t tick = 0; tick < ticksToRun; tick++) {
//            Engine::Tick(ticksClock.getElapsedTime().asSeconds());
//            ticksCurrentSecond++;
//        }
//
//        ticksClock.restart();
//    }
//    if ((ticksClock.getElapsedTime().asMicroseconds()) > (1000000 / tickrate)) {
//        Engine::Tick(ticksClock.restart().asSeconds());
//        ticksCurrentSecond++;
//    }

    if (secondsClock.getElapsedTime().asMicroseconds() > 1000000) {
        ticksLastSecond = ticksCurrentSecond;
        ticksCurrentSecond = 0;

        if (ticksLastSecond < tickrate) {
            std::stringstream ss;
            ss << "Cannot keep up, last second only had " << ticksLastSecond << " / " << tickrate << " ticks";
            Logging::Instance().Log(ss.str());
        }
        if (ticksLastSecond > tickrate) {
            std::stringstream ss;
            ss << "Too many ticks last second: " << ticksLastSecond << " / " << tickrate << " ticks";
            Logging::Instance().Log(ss.str());
        }

        framesLastSecond = framesCurrentSecond;
        framesCurrentSecond = 0;

        secondsClock.restart();
    }
}

void Engine::Tick(float delta) {
    if (scene) {
        scene->Think(delta);
    }
}

void Engine::Render(sf::RenderTarget& renderTarget) {
    if (scene) {
        scene->Render(renderTarget);
    }

    Engine::DrawDebugString(renderTarget);

    lastFrameTime = frameClock.getElapsedTime().asMicroseconds();
    framesCurrentSecond++;
}

void Engine::DrawDebugString(sf::RenderTarget& target) const {
    if (drawDebugString) {
        sf::Text text(std::string("fps: ") +
                      std::to_string(framesLastSecond) +
                      std::string(" / tickrate: ") +
                      std::to_string(ticksLastSecond), renderFont, 16);

        text.setPosition(0.0f, 0.0f);

        auto view = target.getView();
        auto debugView = sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
        target.setView(debugView);
        target.draw(text);
        target.setView(view);
    }
}
