#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list> 
#include "eventSystem.hpp"
#include "coolant.h"
#include "progressBar.h"
#include "renderSystem.hpp"

class Game; // Forward reference to game


/******************************************************************************
 * Cooler:                                                                    *
 *      -An "Ice Cooler" that the player can click on to retrieve coolants.   *
 *       Has a cooldown timer, can make 1 coolant every 6 seconds.            *
 *      -A derived class of Drawable, MouseUpObserver, MouseMoveObserver.     *
 * Visual:                                                                    *
 *      -A blue ice-cooler with a lid that opens when the mouse is over it.   *
 *      -A progress bar displays under it to show the cooldown time.          *
 ******************************************************************************/
class Cooler : public sf::Drawable, public EventSystem::MouseUpObserver, public EventSystem::MouseMoveObserver {
    public:
        Cooler(sf::Vector2f aP);
        Cooler(float aPX, float aPY);
        void getCoolant(sf::Vector2f pos); // Spawns a new coolant in the given position and assigns it as the Game's draggable
        void onMouseOver(bool mouseOver); // Sets open to the mouseOver value passed
        bool isMouseOver(); // Returns true if open (which is only true when the mouse if over this)
        virtual void mouseUp(sf::Event::MouseButtonEvent event); // Calls getCoolant
        virtual void mouseMove(sf::Event::MouseMoveEvent event);
        void update(sf::Time deltaTime);
        sf::FloatRect getGlobalBounds(); // Returns the bounds this object occupies

    private:
        sf::Texture coolerTexture;
        sf::Texture coolantTexture;
        sf::Sprite coolerOpenSprite;
        sf::Sprite coolerClosedSprite;
        sf::FloatRect closedFloatRect; // "Hitbox" of the cooler that can be mouse-overed. 
        sf::Vector2f anchorPoint;
        ProgressBar cooldownTimer; 
        const sf::Vector2f widthHeight = sf::Vector2f(115, 99); // Dimensions of the Cooler sprite
        const float lidHeight = 38.f; // Size of the lid in the cooler sprite, used for calculating bounds.
        const float cooldownTime = 6.f; // Cooldown time between spawning coolants
        bool inCooldown;
        bool open; // Marks whether or not the sprite is the open sprite (true) or closed (false).
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};
