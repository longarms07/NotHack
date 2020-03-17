#include "coolant.h"

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
    std::cout << "The Coolant has been destroyed!\n";
}

void Coolant::onDragEnd(sf::Vector2f position) {
    // Stubbed, check if on target and if a firewall is active. If so cool down the firewall.
    std::cout << "Drag ended on coolant. \n";
    delete this;
}

void Coolant::onDragMove(sf::Vector2f newPosition) {
    coolantSprite.setPosition(newPosition);
}

sf::Sprite Coolant::getSprite() {
    return coolantSprite;
}

void Coolant::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
   renderTarget.draw(coolantSprite, states);
}
