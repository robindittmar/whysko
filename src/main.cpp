#include <iostream>

#include "logging.h"

#include "engine.h"
#include "view_manager.h"

#include "game_scene.h"
#include "waiter.h"
#include "move_intent.h"
#include "wait_intent.h"
#include "work_intent.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


int main() {
    auto& logging = Logging::Instance();
    auto& engine = Engine::Instance();

    auto window = sf::RenderWindow({1280u, 720u}, "whysko");
    auto viewManager = ViewManager(window);

    logging.Log("Initializing engine");
    engine.Initialize();
    engine.SetDrawDebugString(true);

    auto waiter = std::make_shared<Waiter>(1, 100.0f, 100.0f, "img/cat.png");
    auto canna = std::make_shared<Waiter>(2, 500.0f, 500.0f, "img/canna.png");
    auto waiter2 = std::make_shared<Waiter>(3, 500.0f, 500.0f, "img/cat2.png");

    waiter->PushIntents({
        std::make_shared<WaitIntent>(10.0f),
        std::make_shared<WorkIntent>(1.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 25.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 25.0f),
        std::make_shared<WorkIntent>(5.0f)
    });

    canna->PushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 10.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 1900.0f), 50.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 30.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 100.0f), 25.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 40.0f),
    });

    waiter2->PushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 250.0f),
        std::make_shared<WorkIntent>(10.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 350.0f),
        std::make_shared<WorkIntent>(5.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(500.0f, 500.0f), 250.0f),
        std::make_shared<WaitIntent>(2.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 1000.0f),
        std::make_shared<WorkIntent>(30.0f)
    });

    auto scene = std::make_shared<GameScene>();
    scene->AddActor(waiter);
    scene->AddActor(canna);
    scene->AddActor(waiter2);
    scene->Setup();

    engine.SetScene(scene);

    auto backgroundMsc = sf::Music();
    backgroundMsc.openFromFile("snd/track.wav");
    backgroundMsc.play();

    while (window.isOpen()) {
        sf::Event event {};
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            viewManager.HandleEvent(event);
        }

        engine.Think();

        window.clear(sf::Color(0, 130, 175));
        engine.Render(window);
        window.display();
    }

    logging.Log("Shutting down engine");
    engine.Shutdown();
}
