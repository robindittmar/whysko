#ifndef WHYSKO_VIEW_MANAGER_H
#define WHYSKO_VIEW_MANAGER_H

#include "SFML/Graphics/RenderWindow.hpp"


class ViewManager {
public:
    explicit ViewManager(sf::RenderWindow& wnd);
    ~ViewManager() = default;

    void HandleEvent(sf::Event& event);

    void StartDragging(int x, int y);
    void Drag(int x, int y);
    void StopDragging();

    void Zoom(int delta);
private:
    sf::RenderWindow& window;
    sf::View previousView;

    bool isDragging = false;
    sf::Vector2f dragOrigin;
};


#endif //WHYSKO_VIEW_MANAGER_H
