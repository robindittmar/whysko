#ifndef WHYSKO_VIEW_MANAGER_H
#define WHYSKO_VIEW_MANAGER_H

#include "SFML/Graphics/RenderWindow.hpp"


class ViewManager {
public:
    explicit ViewManager(sf::RenderWindow& wnd);
    ~ViewManager() = default;

    void handleEvent(sf::Event& event);

    void startDragging(int x, int y);
    void drag(int x, int y);
    void stopDragging();

    void zoom(int delta);

private:
    sf::RenderWindow& window;
    sf::View previousView;

    bool isDragging = false;
    sf::Vector2f dragOrigin;
};


#endif//WHYSKO_VIEW_MANAGER_H
