#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list> 

class Cooler : public sf::Drawable {
    public:
        Cooler(sf::Vector2f aP);
        Cooler(float aPX, float aPY);
        void getCoolant();
        void onMouseOver(bool mouseOver);
        bool isMouseOver();
        void onClick();
        sf::FloatRect getGlobalBounds();
    private:
        sf::Texture coolerTexture;
        sf::Sprite coolerOpenSprite;
        sf::Sprite coolerClosedSprite;
        sf::FloatRect closedFloatRect;
        sf::Vector2f anchorPoint;
        const sf::Vector2f widthHeight = sf::Vector2f(115, 99);
        const float lidHeight = 38.f;
        bool open;
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};

Cooler::Cooler(sf::Vector2f aP) {
    anchorPoint = aP;
    if (!coolerTexture.loadFromFile("Cooler.png")) {
        std::cout << "Error! Could not load Cooler.png!!!";
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

Cooler::Cooler(float aPX, float aPY) {
    anchorPoint = sf::Vector2f(aPX, aPY);
    if (!coolerTexture.loadFromFile("Cooler.png")) {
        std::cout << "Error! Could not load Cooler.png!!!";
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

void Cooler::onClick() {
    getCoolant();
}

void Cooler::getCoolant() {
    //stubbed;
}

sf::FloatRect Cooler::getGlobalBounds() {
    return closedFloatRect;
}

void Cooler::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(open) renderTarget.draw(coolerOpenSprite, states);
    else renderTarget.draw(coolerClosedSprite, states);
}