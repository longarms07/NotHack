#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list> 
#include "coolant.h"

class Game;

class Cooler : public sf::Drawable {
    public:
        Cooler(sf::Vector2f aP, Game* g);
        Cooler(float aPX, float aPY, Game* g);
        void getCoolant(sf::Vector2f pos); 
        void onMouseOver(bool mouseOver); // Sets open to the mouseOver value passed
        bool isMouseOver(); // Returns true if open (which is only true when the mouse if over this)
        void onClick(sf::Vector2f pos); 
        sf::FloatRect getGlobalBounds(); // Returns the bounds this object occupies
    private:
        sf::Texture coolerTexture;
        sf::Texture coolantTexture;
        sf::Sprite coolerOpenSprite;
        sf::Sprite coolerClosedSprite;
        sf::FloatRect closedFloatRect;
        sf::Vector2f anchorPoint;
        Game* game;
        const sf::Vector2f widthHeight = sf::Vector2f(115, 99); // Dimensions of the Cooler sprite
        const float lidHeight = 38.f; // Size of the lid in the cooler sprite, used for calculating bounds.
        bool open;
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};
