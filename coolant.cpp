#include "coolant.h"
#include "renderSystem.hpp"
#include <iostream>

Coolant::Coolant(sf::Vector2f pos, HackerWindow* hW, sf::Texture& coolantTexture)
    :coolantSprite() 
    {
        if (hW == NULL) {
            std::cout << "Error! Null pointer exception in Coolant's Hackerwindow!!!\n";
            exit (8);
        }
        coolantSprite.setTexture(coolantTexture);  
        coolantSprite.setPosition(pos);
        target = hW;  
        std::cout << "A Coolant has been made!!!\n";
}

Coolant::~Coolant() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(&getSprite());
    std::cout << "The Coolant has been destroyed!\n";
}

void Coolant::onDragEnd(sf::Vector2f position) {
    if (target->contains(position)) target->coolFireWall();
    std::cout << "Drag ended on coolant. \n";
    delete this; // Coolants are only ever created with the "new" keyword
}

void Coolant::onDragMove(sf::Vector2f newPosition) {
    coolantSprite.setPosition(newPosition);
}

const sf::Sprite& Coolant::getSprite() {
    return coolantSprite;
}

void Coolant::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
   renderTarget.draw(coolantSprite, states);
}
