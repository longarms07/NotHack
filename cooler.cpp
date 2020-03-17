#include "cooler.h"
#include "game.h"

Cooler::Cooler(sf::Vector2f aP, Game* g) {
    game = g;
    anchorPoint = aP;
    if (!coolerTexture.loadFromFile("Cooler.png")) {
        std::cout << "Error! Could not load Cooler.png!!!";
        exit (8);
    }
    if (!coolantTexture.loadFromFile("Coolant.png")) {
        std::cout << "Error! Could not load Coolant.png!!!";
        exit (8);
    }
    coolerOpenSprite.setTexture(coolerTexture);
    coolerOpenSprite.setTextureRect(sf::IntRect(0,0,widthHeight.x, widthHeight.y));
    coolerOpenSprite.setPosition(anchorPoint);
    coolerClosedSprite.setTexture(coolerTexture);
    coolerClosedSprite.setTextureRect(sf::IntRect(widthHeight.x,0,widthHeight.x, widthHeight.y));
    coolerClosedSprite.setPosition(anchorPoint);
    closedFloatRect = sf::FloatRect(anchorPoint.x, anchorPoint.y+lidHeight, widthHeight.x, widthHeight.y-lidHeight);
    open = false;
}

Cooler::Cooler(float aPX, float aPY, Game* g) {
    game = g;
    anchorPoint = sf::Vector2f(aPX, aPY);
    if (!coolerTexture.loadFromFile("Cooler.png")) {
        std::cout << "Error! Could not load Cooler.png!!!";
        exit (8);
    }
    if (!coolantTexture.loadFromFile("Coolant.png")) {
        std::cout << "Error! Could not load Coolant.png!!!";
        exit (8);
    }
    coolerOpenSprite.setTexture(coolerTexture);
    coolerOpenSprite.setTextureRect(sf::IntRect(0,0,widthHeight.x, widthHeight.y));
    coolerOpenSprite.setPosition(anchorPoint);
    coolerClosedSprite.setTexture(coolerTexture);
    coolerClosedSprite.setTextureRect(sf::IntRect(widthHeight.x,0,widthHeight.x, widthHeight.y));
    coolerClosedSprite.setPosition(anchorPoint);
    closedFloatRect = sf::FloatRect(anchorPoint.x, anchorPoint.y+lidHeight, widthHeight.x, widthHeight.y-lidHeight);
    open = false;
}

void Cooler::onMouseOver(bool mouseOver) {
    open = mouseOver;   
}

bool Cooler::isMouseOver() {
    return open;
}

void Cooler::onClick(sf::Vector2f pos) {
    getCoolant(pos);
}

void Cooler::getCoolant(sf::Vector2f pos) {
    Coolant* c  = new Coolant(pos, game->getHackerWindow(), coolantTexture);
    game->setDraggable(dynamic_cast<IDraggable*>(c));
}

sf::FloatRect Cooler::getGlobalBounds() {
    return closedFloatRect;
}

void Cooler::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(open) renderTarget.draw(coolerOpenSprite, states);
    else renderTarget.draw(coolerClosedSprite, states);
}