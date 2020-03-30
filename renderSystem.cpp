#include "renderSystem.hpp"
#include <algorithm>

bool RenderSystem::RenderHandler::registerDrawable(const sf::Drawable* drawable) {
    if (std::find(drawableRegistrants.begin(), drawableRegistrants.end(), drawable) != drawableRegistrants.end()) {
       return false;
    } else {
        drawableRegistrants.push_back(drawable);
        return true;
    }
}

bool RenderSystem::RenderHandler::unregisterDrawable(const sf::Drawable* drawable) {
    if (std::find(drawableRegistrants.begin(), drawableRegistrants.end(), drawable) != drawableRegistrants.end()) {
       drawableRegistrants.remove(drawable);
       return true;
    } else {
        return false;
    }
}

void RenderSystem::RenderHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const sf::Drawable* drawable : drawableRegistrants) {
        target.draw(*drawable, states);
    }
}