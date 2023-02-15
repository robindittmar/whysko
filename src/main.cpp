#include <iostream>

#include "engine.h"

#include "game_scene.h"
#include "waiter.h"
#include "move_intent.h"
#include "wait_intent.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "work_intent.h"


int main() {
    auto& engine = Engine::Instance();

    auto window = sf::RenderWindow({1280u, 720u}, "whysko");

    engine.Initialize();
    engine.SetDrawDebugString(true);

    auto waiter = std::make_shared<Waiter>(1, 100.0f, 100.0f, "img/cat.png");
    auto canna = std::make_shared<Waiter>(2, 500.0f, 500.0f, "img/canna.png");
    auto waiter2 = std::make_shared<Waiter>(3, 500.0f, 500.0f, "img/cat2.png");

    waiter->PushIntents({
        std::make_shared<WaitIntent>(10.0f),
        std::make_shared<WorkIntent>(1.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 10.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 10.0f),
        std::make_shared<WorkIntent>(5.0f)
    });

    canna->PushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 0.5f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 1900.0f), 0.5f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 0.5f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 100.0f), 0.5f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 0.5f),
    });

    waiter2->PushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 3.0f),
        std::make_shared<WorkIntent>(10.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 5.0f),
        std::make_shared<WorkIntent>(5.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(500.0f, 500.0f), 3.0f),
        std::make_shared<WaitIntent>(2.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 10.0f),
        std::make_shared<WorkIntent>(30.0f)
    });

    auto scene = std::make_shared<GameScene>();
    scene->AddActor(waiter);
    scene->AddActor(canna);
    scene->AddActor(waiter2);
    scene->Setup();

    engine.SetScene(scene);

    sf::View oldView;
    sf::Vector2f clickPosition;
    bool shiftView = false;

    while (window.isOpen()) {
        sf::Event event {};
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Key::W) {
                }
            } else if (event.type == sf::Event::MouseMoved) {
                if (shiftView) {
                    auto view = oldView;
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y), oldView);
                    view.move(clickPosition.x - mousePos.x, clickPosition.y - mousePos.y);
                    window.setView(view);
                } else {
                    sf::Vector2f target = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
//                clickPosition.x = event.mouseButton.x;
//                clickPosition.y = event.mouseButton.y;
                clickPosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                oldView = window.getView();

                shiftView = true;
            } else if (event.type == sf::Event::MouseButtonReleased) {
                shiftView = false;
            }
            else if (event.type == sf::Event::MouseWheelMoved) {
                auto view = window.getView();

                auto size = view.getSize();

                size.x -= (size.x / 10) * event.mouseWheel.delta;
                size.y -= (size.y / 10) * event.mouseWheel.delta;

                view.setSize(size);
                window.setView(view);
            }
        }

        engine.Think();

        window.clear();
        engine.Render(window);
        window.display();
    }

    engine.Shutdown();
}
