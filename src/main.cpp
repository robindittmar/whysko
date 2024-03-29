#include "engine/logging.h"

#include "engine/engine.h"
#include "engine/input_manager.h"
#include "engine/view_manager.h"

#include "entities/move_intent.h"
#include "entities/player.h"
#include "entities/wait_intent.h"
#include "entities/waiter.h"
#include "entities/work_intent.h"
#include "scenes/game_scene.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


int main() {
    auto& logging = Logging::instance();
    auto& engine = Engine::instance();
    auto& inputManager = InputManager::instance();

    auto window = sf::RenderWindow({1280u, 720u}, "whysko");
    auto viewManager = ViewManager(window);
    inputManager.init(&window);

    logging.log("Initializing engine");
    engine.initialize();
    engine.getDebugView().setVisible(true);
    //    engine.setFramerate(300);

    auto player = std::make_shared<Player>();
    auto waiter0 = std::make_shared<Waiter>(1, 100.0f, 100.0f, "img/cat.png");
    auto waiter1 = std::make_shared<Waiter>(2, 500.0f, 500.0f, "img/cat.png");
    auto waiter2 = std::make_shared<Waiter>(3, 500.0f, 500.0f, "img/cat2.png");
    auto waiter3 = std::make_shared<Waiter>(4, 300.0f, 300.0f, "img/cat2.png");

    player->setDrawHitbox(true);

    waiter0->pushIntents({
        std::make_shared<WaitIntent>(10.0f),
        std::make_shared<WorkIntent>(1.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 25.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 25.0f),
        std::make_shared<WorkIntent>(5.0f),
    });

    waiter1->pushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 10.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 1900.0f), 50.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 30.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 100.0f), 25.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 40.0f),
    });

    waiter2->pushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 250.0f),
        std::make_shared<WorkIntent>(10.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1900.0f, 1900.0f), 350.0f),
        std::make_shared<WorkIntent>(5.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(500.0f, 500.0f), 250.0f),
        std::make_shared<WaitIntent>(2.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(100.0f, 100.0f), 1000.0f),
        std::make_shared<WorkIntent>(30.0f),
    });

    waiter3->pushIntents({
        std::make_shared<MoveIntent>(sf::Vector2f(1000.0f, 300.0f), 150.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1000.0f, 900.0f), 150.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(1800.0f, 1800.0f), 150.0f),
        std::make_shared<MoveIntent>(sf::Vector2f(10000.0f, 10000.0f), 1000.0f),
    });

    auto scene = std::make_shared<GameScene>();
    scene->addEntity(player);
    scene->addEntity(waiter0);
    scene->addEntity(waiter1);
    scene->addEntity(waiter2);
    scene->addEntity(waiter3);
    scene->setup();

    engine.setScene(scene);

    auto backgroundMsc = sf::Music();
    backgroundMsc.openFromFile("snd/track.wav");
    //    backgroundMsc.play();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            inputManager.handleEvent(event);
            viewManager.handleEvent(event);
        }

        engine.think();

        window.clear(sf::Color(0, 130, 175));
        engine.render(window);
        window.display();

        engine.postRender();
    }

    logging.log("Shutting down engine");
    engine.shutdown();
}
