#include <iostream>

#include "logging.h"

#include "engine.h"
#include "view_manager.h"

#include "game_scene.h"
#include "move_intent.h"
#include "wait_intent.h"
#include "waiter.h"
#include "work_intent.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


int main() {
    auto& logging = Logging::instance();
    auto& engine = Engine::instance();

    auto window = sf::RenderWindow({1280u, 720u}, "whysko");
    auto viewManager = ViewManager(window);

    window.setFramerateLimit(300);

    logging.log("Initializing engine");
    engine.initialize();
    engine.setDrawDebugString(true);

    auto waiter = std::make_shared<Waiter>(1, 100.0f, 100.0f, "img/cat.png");
    auto canna = std::make_shared<Waiter>(2, 500.0f, 500.0f, "img/canna.png");
    auto waiter2 = std::make_shared<Waiter>(3, 500.0f, 500.0f, "img/cat2.png");

    waiter->pushIntents({std::make_shared<WaitIntent>(10.0f),
                         std::make_shared<WorkIntent>(1.0f),
                         std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 25.0f),
                         std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 25.0f),
                         std::make_shared<WorkIntent>(5.0f)});

    canna->pushIntents({
            std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 10.0f),
            std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 1900.0f), 50.0f),
            std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 30.0f),
            std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 100.0f), 25.0f),
            std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 40.0f),
    });

    waiter2->pushIntents({std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 250.0f),
                          std::make_shared<WorkIntent>(10.0f),
                          std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 350.0f),
                          std::make_shared<WorkIntent>(5.0f),
                          std::make_shared<MoveIntent>(sf::Vector2f(500.0f, 500.0f), 250.0f),
                          std::make_shared<WaitIntent>(2.0f),
                          std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 1000.0f),
                          std::make_shared<WorkIntent>(30.0f)});

    auto scene = std::make_shared<GameScene>();
    scene->addActor(waiter);
    scene->addActor(canna);
    scene->addActor(waiter2);
    scene->setup();

    engine.setScene(scene);

    auto backgroundMsc = sf::Music();
    backgroundMsc.openFromFile("snd/track.wav");
    //    backgroundMsc.play();

    while (window.isOpen()) {
        sf::Event event{};
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            viewManager.handleEvent(event);
        }

        engine.think();

        window.clear(sf::Color(0, 130, 175));
        engine.render(window);
        window.display();
    }

    logging.log("Shutting down engine");
    engine.shutdown();
}
