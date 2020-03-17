#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "idraggable.h"
#include "hackerWindow.h"

class Coolant : public IDraggable {
    public:
        Coolant(sf::Vector2f pos, HackerWindow* hW, sf::Texture& coolantTexture);
        ~Coolant();
        virtual void onDragEnd(sf::Vector2f position);
        virtual void onDragMove(sf::Vector2f newPosition);
        virtual sf::Sprite getSprite();

    private:
        HackerWindow* target;
        sf::Sprite coolantSprite;
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};