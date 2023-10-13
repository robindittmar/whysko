#ifndef WHYSKO_DEBUG_VIEW_H
#define WHYSKO_DEBUG_VIEW_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"


class DebugView {
public:
    DebugView() = default;
    ~DebugView() = default;

    void init();

    void addStaticValue(const std::string& key, const std::string& value);
    void addDynamicValue(const std::string& key, uint32_t* value);

    void removeStaticValue(const std::string& key);
    void removeDynamicValue(const std::string& key);

    void render(sf::RenderTarget& renderTarget);

    inline bool getVisible() const;
    inline void setVisible(bool v);

private:
    bool visible = false;

    sf::Font renderFont;
    sf::Text renderText;

    std::map<std::string, std::string> staticDebugValues;
    std::map<std::string, uint32_t*> dynamicDebugValues;
};

bool DebugView::getVisible() const {
    return visible;
}

void DebugView::setVisible(bool v) {
    visible = v;
}

#endif//WHYSKO_DEBUG_VIEW_H
