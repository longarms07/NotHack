#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "idraggable.h"
#include "hackerWindow.h"

// This class implements IDraggable
class Coolant : public IDraggable {
    public:
        /* Takes a starting position for the sprite,
           A pointer to the HackerWindow that we want to drop the coolant on,
           And a reference to the texture to use as input. */
        Coolant(sf::Vector2f pos, HackerWindow* hW, sf::Texture& coolantTexture);
        ~Coolant();
        /* If the drag ends within the bounds of a HackerWindow with an active firewall,
           It applies the coolant to the firewall. 
           at the end of this function the coolant destroys itself. */
        virtual void onDragEnd(sf::Vector2f position); 
        virtual void onDragMove(sf::Vector2f newPosition); // Updates the sprite position
        virtual sf::Sprite getSprite(); // Returns the sprite to draw

    private:
        HackerWindow* target; // A pointer towards the target HackerWindow
        sf::Sprite coolantSprite;
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};