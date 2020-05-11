#pragma once
#include <SFML/Graphics.hpp>


/******************************************************************************
 * IDraggable:                                                                *
 *      -An Abstract Class Interface to be used for objects draggable by the  *
 *          mouse.                                                            *
 * Note: Only 1 IDraggable can be dragged at a time. 
 ******************************************************************************/
class IDraggable : public sf::Drawable {
    public:
        /* In order to make this an abstract class, it must have pure virtual methods. 
        These are methods that are marked with "= 0".*/
        virtual void onDragEnd(sf::Vector2f position) = 0; // Called when a drag is completed
        virtual void onDragMove(sf::Vector2f newPosition) = 0; // Called when the mouse moves
        virtual sf::Vector2f getPosition() = 0;
        virtual ~IDraggable() { }; // All abstract classes need virtual deconstructors
        

    private:
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const = 0;

};

