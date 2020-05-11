#include "coolant.h"
#include <iostream>
#include "globals.hpp"

/*****************************************************
 * Coolant Constructor -- Constructor for creating   *
 *     instances of Coolants.                        * 
 * Parameters:                                       *
 *    -pos: A Vector2 of floats containing the       *
 *      starting position of the coolant sprite.     *
 *    -coolantTexture: A reference to the texture    *
 *      containing the coolant sprite.               *
 *****************************************************/
Coolant::Coolant(sf::Vector2f pos, sf::Texture& coolantTexture)
    :coolantSprite() 
    {
        // Set up the Coolant Sprite to be drawn
        coolantSprite.setTexture(coolantTexture);  
        coolantSprite.setPosition(pos); 
        //std::cout << "A Coolant has been made!!!\n"; // Debug
        RenderSystem::RenderHandler::getInstance()->registerDrawable(dynamic_cast<Drawable*>(this));
}

/*****************************************************
 * Coolant Deonstructor -- Constructor for           *
 *     destroying instances of Coolants.             * 
 *****************************************************/
Coolant::~Coolant() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(dynamic_cast<Drawable*>(this));
    //std::cout << "The Coolant has been destroyed!\n"; // Debug
}

/*****************************************************
 * OnDragEnd-- Cools down the firewall if the drag   *
 *      ends with the coolant over the hackerWindow. *
 *      Destroys the coolant.                        *
 * Overrides the Virtual function from IDraggable    *
 *****************************************************/
void Coolant::onDragEnd(sf::Vector2f position) {
    if (Globals::hackerWindow->contains(position) && fireWall != NULL) fireWall->coolantApplied();
    //std::cout << "Drag ended on coolant. \n"; // Debug
    delete this; // Coolants are only ever created with the "new" keyword
}

/*****************************************************
 * OnDragMove-- Updates the coolant's position to    *
 *      follow the mouse's.                          *
 * Overrides the Virtual function from IDraggable    *
 *****************************************************/
void Coolant::onDragMove(sf::Vector2f newPosition) {
    coolantSprite.setPosition(newPosition);
}

/*****************************************************
 * getPosition-- Getter method for the Coolant's     *
 *      current position.                            *
 * Overrides the Virtual function from IDraggable    *
 *****************************************************/
sf::Vector2f Coolant::getPosition() {
    return coolantSprite.getPosition();
}

/*****************************************************
 * setFireWall-- STATIC METHOD                       *
 *      Sets the current target firewall for         *
 *      coolants to cool down.                       *
 *****************************************************/
void Coolant::setFireWall(Complication::FireWall* pointer) {
    fireWall = pointer;
}

/*****************************************************
 * draw -- Renders the Coolant graphics.             *
 * Overrides the Virtual function from Drawable.     *
 *****************************************************/
void Coolant::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
   renderTarget.draw(coolantSprite, states);
}
