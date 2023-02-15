#include "engine.h"
#include "SFML/Graphics/Text.hpp"


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
    if (ticksClock.getElapsedTime().asMicroseconds() > 1000000 / tickrate) {
        Engine::Tick();

        ticksCurrentSecond++;
        ticksClock.restart();
    }

    if (secondsClock.getElapsedTime().asMicroseconds() > 1000000) {
        ticksLastSecond = ticksCurrentSecond;
        ticksCurrentSecond = 0;

        framesLastSecond = framesCurrentSecond;
        framesCurrentSecond = 0;

        secondsClock.restart();
    }
}

void Engine::Tick() {
    if (scene) {
        scene->Think();
    }
}

void Engine::Render(sf::RenderTarget& renderTarget) {
    if (scene) {
        scene->Render(renderTarget);
    }

    Engine::DrawDebugString(renderTarget);
    framesCurrentSecond++;
}

void Engine::DrawDebugString(sf::RenderTarget& target) const {
    if (drawDebugString) {
        auto view = target.getView();
        auto debugView = sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));

        sf::Text text(std::string("fps: ") +
                      std::to_string(framesLastSecond) +
                      std::string(" / tickrate: ") +
                      std::to_string(ticksLastSecond), renderFont, 16);

        text.setPosition(0.0f, 0.0f);

        target.setView(debugView);
        target.draw(text);
        target.setView(view);
    }
}
