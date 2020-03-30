#pragma once
#include <SFML/Graphics.hpp>
//Interface for Draggable Objects
class IDraggable {
    public:
        // In order to make this an abstract class, it must have pure virtual methods. These are methods that are marked with "= 0".
        virtual void onDragEnd(sf::Vector2f position) = 0; // Called when a drag is completed
        virtual void onDragMove(sf::Vector2f newPosition) = 0; // Called when the mouse moves
        virtual const sf::Sprite& getSprite() = 0; // Returns the sprite of the object. Since this could not implement drawable, the draggable must be drawn through the sprite.
        virtual ~IDraggable() { }; // All abstract classes need virtual deconstructors
        

    private:
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const = 0;

};

