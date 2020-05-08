#include "cooler.h"
#include "game.h"
#include "globals.hpp"

/******************************************************************************
 * Cooler Constructor -- Constructor for creating a new instance of a Cooler. *
 * Parameters:                                                                *
 *      -aP: A Vector2 of Floats representing the anchor point at which the   *
 *       coolant is drawn.                                                    *
 ******************************************************************************/
Cooler::Cooler(sf::Vector2f aP)
    : cooldownTimer(sf::Vector2f(aP.x+60, aP.y+210), sf::Vector2f(150, 32), sf::Color::Blue, 6.f, "Making Coolant...", 17) {
    anchorPoint = aP;

    // Load the cooler and coolant textures
    if (!coolerTexture.loadFromFile("Cooler.png")) {
        std::cout << "Error! Could not load Cooler.png!!!";
        exit (8);
    }
    if (!coolantTexture.loadFromFile("Coolant.png")) {
        std::cout << "Error! Could not load Coolant.png!!!";
        exit (8);
    }

    // Initialize the cooler sprites
    coolerOpenSprite.setTexture(coolerTexture);
    coolerOpenSprite.setTextureRect(sf::IntRect(0,0,widthHeight.x, widthHeight.y));
    coolerOpenSprite.setPosition(anchorPoint);
    coolerOpenSprite.setScale(2.f, 2.f);
    coolerClosedSprite.setTexture(coolerTexture);
    coolerClosedSprite.setTextureRect(sf::IntRect(widthHeight.x,0,widthHeight.x, widthHeight.y));
    coolerClosedSprite.setPosition(anchorPoint);
    coolerClosedSprite.setScale(2.f, 2.f);
    closedFloatRect = sf::FloatRect(anchorPoint.x, anchorPoint.y+lidHeight, 2*widthHeight.x, 2*widthHeight.y-lidHeight);
    
    open = false;
    inCooldown = false;
}

/******************************************************************************
 * OVERLOAD                                                                   *
 * Cooler Constructor -- Constructor for creating a new instance of a Cooler. *
 * Parameters:                                                                *
 *      -aPX: A Float representing the X value of the anchor point            *
 *      -aPY: A Float representing the Y value of the anchor point            *
 ******************************************************************************/
Cooler::Cooler(float aPX, float aPY) 
    : Cooler(sf::Vector2f(aPX, aPY))
{ }

/******************************************************************************
 * onMouseOver -- Opens the cooler if the mouse is over it, closes the cooler *
 *      if not.                                                               *
 * Parameters:                                                                *
 *      -mouseOver: True if the mouse is over the cooler, false if not.       *
 *       coolant is drawn.                                                    *
 ******************************************************************************/
void Cooler::onMouseOver(bool mouseOver) {
    open = mouseOver;   
}

/******************************************************************************
 * isMouseOver -- Getter method for cooler state (open or closed)             *
 * Returns:                                                                   *
 *      -True if the cooler is open (mouse is over it)                        *
 *      -False if the cooler is closed (mouse is not over it)                 *
 ******************************************************************************/
bool Cooler::isMouseOver() {
    return open;
}

/******************************************************************************
 * mouseUp -- Called by the EventSystem when the mouse button is clicked.     *
 *      Calls getCoolant if the mouse is over the cooler.                     *
 * Parameters:                                                                *
 *      -event: A MouseButtonEvent                                            *
 * Overrides the Virtual function from MouseUpObserver                        *
 ******************************************************************************/
void Cooler::mouseUp(sf::Event::MouseButtonEvent event) {
    sf::Vector2f pos = sf::Vector2f(event.x, event.y);
    if (getGlobalBounds().contains(pos))
        getCoolant(pos);
}


/******************************************************************************
 * mouseMove -- Called by the EventSystem when the mouse moves.               *
 *      Toggles "onMouseOver" depending on the mouse's position.              *
 * Parameters:                                                                *
 *      -event: A MouseMoveEvent                                              *
 * Overrides the Virtual function from MouseMoveObserver                      *
 ******************************************************************************/
void Cooler::mouseMove(sf::Event::MouseMoveEvent event){
    if(getGlobalBounds().contains(sf::Vector2f(event.x, event.y))) {
        if(!isMouseOver()) onMouseOver(true);
    }
    else if (isMouseOver()) onMouseOver(false);
}

/******************************************************************************
 * getCoolant -- Creates a coolant (if able to) and sets it as the Game's     *
 *      current IDraggable.                                                   *
 * Parameters:                                                                *
 *      -pos: A Vector2 of Floats containing the mouse position.              *
 ******************************************************************************/
void Cooler::getCoolant(sf::Vector2f pos) {
    if (!inCooldown) {
        // Make the Coolant
        Coolant* c  = new Coolant(pos, coolantTexture);
        Globals::game->setDraggable(dynamic_cast<IDraggable*>(c)); // Must cast the coolant as an IDraggable;
        // Start the Cooldown
        cooldownTimer.setProgress(0);
        inCooldown = true;
    }
}
/******************************************************************************
 * update -- Called every frame. If in cooldown, updates the cooldown time    *
 *      and ends it after enough time passes.                                 *
 * Parameters:                                                                *
 *      -deltaTime: the time since the last frame.                            *
 ******************************************************************************/
void Cooler::update(sf::Time deltaTime) {
    if (inCooldown) {
        cooldownTimer.incrementProgress(deltaTime.asSeconds());
        if (cooldownTimer.getProgress() == cooldownTime) inCooldown = false;
    }
}

/******************************************************************************
 * getGlobalBounds -- Getter method for the cooler's clickable bounds.        *
 * Returns:                                                                   *
 *      -The global bounds of the closedFloatRect.                            *
 ******************************************************************************/
sf::FloatRect Cooler::getGlobalBounds() {
    return closedFloatRect;
}

/******************************************************************************
 * draw -- Renders the Cooler graphics.                                       *
 * Overrides the Virtual function from Drawable.                              *
 ******************************************************************************/
void Cooler::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if (open) {
        renderTarget.draw(coolerOpenSprite, states); // Draw the open sprite if the mouse is over the cooler
    } else {
        renderTarget.draw(coolerClosedSprite, states); // Draw the closed sprite if the mouse is not over the cooler
    }

    if (inCooldown) {
        renderTarget.draw(cooldownTimer, states); // Draw the cooldown progress bar when in cooldown.
    }
}