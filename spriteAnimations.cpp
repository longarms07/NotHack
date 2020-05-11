#pragma once
#include "spriteAnimations.hpp"
#include <cmath>
#include <iostream>

/***************************
 * Parameters:
 *  - sf::Sprite* spriteToWrap: Pointer to sprite to animate and draw
 *  - float pHeight: amplitude of sine (how far left and right the object moves)
 *  - float pPeriod: duration of the animation in seconds
 *  - float startTime: Option to start mid-animation
 ***************************/
SpriteAnimations::HorizontalSine::HorizontalSine(sf::Sprite* spriteToWrap, float pHeight, float pPeriod, float startTime) {
    originalSprite = spriteToWrap;

    height = pHeight;
    period = pPeriod; // Get rid of the 2*PI period

    currentTime = fmod(startTime, period);
}

SpriteAnimations::HorizontalSine::~HorizontalSine() {
    delete originalSprite;
}

/***********************
 * Update the animation, given how much time has passed
 *
 * Parameters:
 *  - sf::deltaTime: time since last frame
 ***********************/
void SpriteAnimations::HorizontalSine::update(sf::Time deltaTime) {
    currentTime = fmod((currentTime + deltaTime.asSeconds()), period*(2.f*3.1516f));

    sf::Vector2f oldPosition = originalSprite->getPosition();
    float sineOffset = height*sin((2.f*3.1516f)*currentTime/period)-height; // Make it so the animation never moves farther left than where it starter
    originalSprite->setPosition(oldPosition.x+sineOffset, oldPosition.y);
}

void SpriteAnimations::HorizontalSine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*originalSprite, states);
}

sf::Sprite& SpriteAnimations::HorizontalSine::getSprite() {
    return *originalSprite;
}