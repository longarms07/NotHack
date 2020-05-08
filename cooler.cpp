#include "cooler.h"
#include "game.h"
#include "globals.hpp"

Cooler::Cooler(sf::Vector2f aP)
    : cooldownTimer(sf::Vector2f(aP.x+60, aP.y+210), sf::Vector2f(150, 32), sf::Color::Blue, 6.f, "Making Coolant...", 17) {
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
    coolerOpenSprite.setScale(2.f, 2.f);
    coolerClosedSprite.setTexture(coolerTexture);
    coolerClosedSprite.setTextureRect(sf::IntRect(widthHeight.x,0,widthHeight.x, widthHeight.y));
    coolerClosedSprite.setPosition(anchorPoint);
    coolerClosedSprite.setScale(2.f, 2.f);
    closedFloatRect = sf::FloatRect(anchorPoint.x, anchorPoint.y+lidHeight, 2*widthHeight.x, 2*widthHeight.y-lidHeight);
    open = false;
    inCooldown = false;
}

Cooler::Cooler(float aPX, float aPY) 
    : Cooler(sf::Vector2f(aPX, aPY))
{ }

void Cooler::onMouseOver(bool mouseOver) {
    open = mouseOver;   
}

bool Cooler::isMouseOver() {
    return open;
}

void Cooler::mouseUp(sf::Event::MouseButtonEvent event) {
    sf::Vector2f pos = sf::Vector2f(event.x, event.y);
    if (getGlobalBounds().contains(pos))
        getCoolant(pos);
}

void Cooler::mouseMove(sf::Event::MouseMoveEvent event){
    if(getGlobalBounds().contains(sf::Vector2f(event.x, event.y))) {
        if(!isMouseOver()) onMouseOver(true);
    }
    else if (isMouseOver()) onMouseOver(false);
}

void Cooler::getCoolant(sf::Vector2f pos) {
    if (!inCooldown) {
        Coolant* c  = new Coolant(pos, coolantTexture);
        Globals::game->setDraggable(dynamic_cast<IDraggable*>(c)); // Must cast the coolant as an IDraggable
        //RenderSystem::RenderHandler::getInstance()->registerDrawable(&c->getSprite());
        cooldownTimer.setProgress(0);
        inCooldown = true;
    }
}

void Cooler::update(sf::Time deltaTime) {
    if (inCooldown) {
        cooldownTimer.incrementProgress(deltaTime.asSeconds());
        if (cooldownTimer.getProgress() == cooldownTime) inCooldown = false;
    }
}

sf::FloatRect Cooler::getGlobalBounds() {
    return closedFloatRect;
}

void Cooler::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if (open) {
        renderTarget.draw(coolerOpenSprite, states);
    } else {
        renderTarget.draw(coolerClosedSprite, states);
    }

    if (inCooldown) {
        renderTarget.draw(cooldownTimer, states);
    }
}