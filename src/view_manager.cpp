#include "view_manager.h"
#include <SFML/Window/Event.hpp>


ViewManager::ViewManager(sf::RenderWindow& wnd)
    : window(wnd) {}

void ViewManager::HandleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        this->Drag(event.mouseMove.x, event.mouseMove.y);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            this->StartDragging(event.mouseButton.x, event.mouseButton.y);
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            this->StopDragging();
        }
    }
    else if (event.type == sf::Event::MouseWheelMoved) {
        this->Zoom(event.mouseWheel.delta);
    }
}

void ViewManager::StartDragging(int x, int y) {
    isDragging = true;
    dragOrigin = window.mapPixelToCoords(sf::Vector2i(x, y));
    previousView = window.getView();
}

void ViewManager::Drag(int x, int y) {
    if (!isDragging) {
        return;
    }

    auto dragPosition = window.mapPixelToCoords(sf::Vector2i(x, y), previousView);

    auto view = previousView;
    view.move(dragOrigin.x - dragPosition.x, dragOrigin.y - dragPosition.y);
    window.setView(view);
}

void ViewManager::StopDragging() {
    isDragging = false;
}

void ViewManager::Zoom(int delta) {
    if (isDragging) {
        return;
    }

    auto view = window.getView();
    auto size = view.getSize();

    size.x -= (size.x / 10) * (float)delta;
    size.y -= (size.y / 10) * (float)delta;

    view.setSize(size);
    window.setView(view);
}

