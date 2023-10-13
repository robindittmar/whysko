#include "debug_view.h"
#include "engine.h"

#include <sstream>


void DebugView::init() {
    renderFont = Engine::instance().getResourceManager().loadFont("fnt/FiraCode-Regular.ttf");
    renderText = sf::Text("", renderFont, 16);
    renderText.setPosition(0.0f, 0.0f);
}

void DebugView::addStaticValue(const std::string& key, const std::string& value) {
    staticDebugValues[key] = value;
}

void DebugView::addDynamicValue(const std::string& key, uint32_t* value) {
    dynamicDebugValues[key] = value;
}

void DebugView::removeStaticValue(const std::string& key) {
    staticDebugValues.erase(key);
}

void DebugView::removeDynamicValue(const std::string& key) {
    dynamicDebugValues.erase(key);
}

void DebugView::render(sf::RenderTarget& renderTarget) {
    std::stringstream ss;
    for (auto& value : staticDebugValues) {
        ss << value.first << '=' << value.second << '\n';
    }
    for (auto& value : dynamicDebugValues) {
        ss << value.first << '=' << *value.second << '\n';
    }
    renderText.setString(ss.str());

    auto view = renderTarget.getView();

    auto debugView = sf::View(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
    renderTarget.setView(debugView);
    renderTarget.draw(renderText);

    renderTarget.setView(view);
}
