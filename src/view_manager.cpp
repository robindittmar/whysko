#include "view_manager.h"
#include <SFML/Window/Event.hpp>


ViewManager::ViewManager(sf::RenderWindow& wnd)
    : window(wnd) {}

void ViewManager::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        this->drag(event.mouseMove.x, event.mouseMove.y);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            this->startDragging(event.mouseButton.x, event.mouseButton.y);
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            this->stopDragging();
        }
    } else if (event.type == sf::Event::MouseWheelMoved) {
        this->zoom(event.mouseWheel.delta);
    }
}

void ViewManager::startDragging(int x, int y) {
    isDragging = true;
    dragOrigin = window.mapPixelToCoords(sf::Vector2i(x, y));
    previousView = window.getView();
}

void ViewManager::drag(int x, int y) {
    if (!isDragging) {
        return;
    }

    auto dragPosition = window.mapPixelToCoords(sf::Vector2i(x, y), previousView);

    auto view = previousView;
    view.move(dragOrigin.x - dragPosition.x, dragOrigin.y - dragPosition.y);
    window.setView(view);
}

void ViewManager::stopDragging() {
    isDragging = false;
}

void ViewManager::zoom(int delta) {
    if (isDragging) {
        return;
    }

    auto view = window.getView();
    auto size = view.getSize();

    size.x *= 1 - ((float)delta / 12);
    size.y *= 1 - ((float)delta / 12);

    view.setSize(size);
    window.setView(view);
}
