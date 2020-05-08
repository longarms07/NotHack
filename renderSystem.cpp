#include "renderSystem.hpp"
#include <algorithm>

bool RenderSystem::RenderHandler::registerDrawable(const sf::Drawable* drawable, int layer) {
    for (std::list<const sf::Drawable*>* drawLayer : drawableRegistrants) {
        if (std::find(drawLayer->begin(), drawLayer->end(), drawable) != drawLayer->end()) {
           return false;
        }
    }

    if (layer >= drawableRegistrants.size()) {
        for (int i=drawableRegistrants.size(); i<=layer; i++) {
            drawableRegistrants.push_back(new std::list<const sf::Drawable*>);
        }
    }

    drawableRegistrants[layer]->push_back(drawable);
    return true;
}

bool RenderSystem::RenderHandler::unregisterDrawable(const sf::Drawable* drawable) {
    for (std::list<const sf::Drawable*>* drawLayer : drawableRegistrants) {
        if (std::find(drawLayer->begin(), drawLayer->end(), drawable) != drawLayer->end()) {
           drawLayer->remove(drawable);
           return true;
        }
    }

    return false;
}

void RenderSystem::RenderHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (std::list<const sf::Drawable*>* drawLayer : drawableRegistrants) {
        for (const sf::Drawable* drawable : *drawLayer) {
            target.draw(*drawable, states);
        }
    }
}