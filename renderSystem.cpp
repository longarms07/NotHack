#include "renderSystem.hpp"
#include <algorithm>

/************************
 * Adds a sf::Drawable to the render list
 *
 * Parameters:
 *  - sf::Drawable* drawable: pointer to object to register
 *  - int layer (default 0): Render layer to register the sf::Drawable on
 * Returns: If the pointer was registered
 *
 * Note: Objects are rendered in the order of their layer, starting with 0, and (second) by the order they were added (starting with the first)
 *************************/
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

/**********************
 * Remove the given sf::Drawable pointer
 *
 * Returns: If the pointer was removed
 **********************/
bool RenderSystem::RenderHandler::unregisterDrawable(const sf::Drawable* drawable) {
    for (std::list<const sf::Drawable*>* drawLayer : drawableRegistrants) {
        if (std::find(drawLayer->begin(), drawLayer->end(), drawable) != drawLayer->end()) {
           drawLayer->remove(drawable);
           return true;
        }
    }

    return false;
}

/*************************************
 * Objects are rendered in the order of their layer,
 * starting with 0, and (second) by the order they
 * were added (starting with the first).
 *
 * Parameters:
 *  - sf::RenderTarget& target: RenderTarget to draw on
 *  - sf::RenderState: Extra states for the RenderTarget
 *
 * Note: This method is called by Game::render()
 *************************************/
void RenderSystem::RenderHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (std::list<const sf::Drawable*>* drawLayer : drawableRegistrants) {
        for (const sf::Drawable* drawable : *drawLayer) {
            target.draw(*drawable, states);
        }
    }
}