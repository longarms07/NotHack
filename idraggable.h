#pragma once
#include <SFML/Graphics.hpp>
//Interface for Draggable Objects
class IDraggable {
    public:
        virtual void onDragEnd(sf::Vector2f position) = 0;
        virtual void onDragMove(sf::Vector2f newPosition) = 0;
        virtual sf::Sprite getSprite() = 0;
        virtual ~IDraggable() { };
        

    private:
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const = 0;

};

