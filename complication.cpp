#pragma once
#include <iostream>
#include "complication.hpp"
#include "globals.hpp"
#include "spriteAnimations.hpp"

// General Complication Functions

int Complication::Complication::getNumberKeysRequired() {
    return numKeysReq;
}

double Complication::Complication::getPenaltyValue() {
    return penalty;
}

Complication::endData Complication::Complication::getEndData() { 
    return endingData;
}

bool Complication::Complication::isActive() {
    return active;
}

// FireWall Functions 

Complication::FireWall::FireWall(int targetChars, sf::Time maxTime, sf::Time coolTime, int activationKeys, double penaltyAmount)
    : barOffset(0.f, 80.f),
      firewallOffset(-10.f, 0.f)
{
    maxAnchorPoint = Globals::hackerWindow->getAnchorPoint();
    maxBounds = Globals::hackerWindow->getWidthHeight();
    minAnchorPoint = sf::Vector2f(maxAnchorPoint.x, maxAnchorPoint.y+maxBounds.y);
    
    sf::Sprite* fireSprite = new sf::Sprite();
    fireSprite->setPosition(minAnchorPoint);
    fireSprite->setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    fireSprite->setTexture(Globals::computerSpriteSheet);
    fireSprite->setTextureRect(sf::IntRect(2, 7, 348, 326));
    fireLayer1 = new SpriteAnimations::HorizontalSine(fireSprite, 10.f, 0.2f);
    
    fireSprite = new sf::Sprite();
    fireSprite->setPosition(minAnchorPoint);
    fireSprite->setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    fireSprite->setTexture(Globals::computerSpriteSheet);
    fireSprite->setTextureRect(sf::IntRect(367, 26, 348, 326));
    fireLayer2 = new SpriteAnimations::HorizontalSine(fireSprite, 10.f, 0.6f);

    fireSprite = new sf::Sprite();
    fireSprite->setPosition(minAnchorPoint);
    fireSprite->setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    fireSprite->setTexture(Globals::computerSpriteSheet);
    fireSprite->setTextureRect(sf::IntRect(721, 16, 348, 326));
    fireLayer3 = new SpriteAnimations::HorizontalSine(fireSprite, 10.f, 0.4f);
    
    maximumTime = maxTime;
    coolantTime = coolTime;
    elapsedTime = sf::Time::Zero;
    numTargetChars = targetChars;
    numEnteredChars = 0;
    active = false;
    endingData.defeated = false;
    endingData.ended = false;
    penalty = penaltyAmount;
    numKeysReq = activationKeys;
    
    progressBar = new ProgressBar(barOffset+minAnchorPoint, sf::Vector2f(maxBounds.x, 20), sf::Color::Blue, numTargetChars, "Firewall detected... coding anti-fire...", 14);
    
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 1);
    std::cout << "The firewall has been created!\n";
}

Complication::FireWall::~FireWall() {
    delete progressBar;
    delete fireLayer1;
    delete fireLayer2;
    delete fireLayer3;
    Coolant::setFireWall(NULL);
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);

}

void Complication::FireWall::startComplication() {
    active = true;
    Coolant::setFireWall(this);
    updateGraphics();
}

void Complication::FireWall::endComplication(bool defeated) {
    active = false;
    endingData.defeated = defeated;
    endingData.ended = true;
    if (defeated) std::cout << "The firewall has been defeated!\n";
    else std::cout << "The firewall has melted your computer!\n";
}

void Complication::FireWall::keyPressed() {
    if(active) {
        numEnteredChars++;
        std::cout << "The firewall has recieved a char!\n";
        progressBar->incrementProgress(1);
        if (numEnteredChars >= numTargetChars) endComplication(true);
    }
}

void Complication::FireWall::update(sf::Time deltaTime) {
    if(active) {
        elapsedTime+= deltaTime;
        //std::cout << "The firewall has " << (maximumTime.asSeconds()-elapsedTime.asSeconds()) << " seconds left!\n";
        if (elapsedTime >= maximumTime) endComplication(false);
        else {
            updateGraphics();
            fireLayer1->update(deltaTime);
            fireLayer2->update(deltaTime);
            fireLayer3->update(deltaTime);
        }
    }
}

void Complication::FireWall::coolantApplied() {
    if(active) {
        elapsedTime-= coolantTime;
        if(elapsedTime < sf::Time::Zero) elapsedTime = sf::Time::Zero;
        updateGraphics();
    }
}

void Complication::FireWall::updateGraphics() {
    if(active) {
        // Step 1: Get the percentage of the time that is left. 
        // This is done by dividing the elapsed time by the maximum time.
        float elapsedTimePercent = elapsedTime.asSeconds() / maximumTime.asSeconds();
        //if(elapsedTimePercent > 1) elapsedTimePercent == 1;
        // Step 2: Calculate the height the wallGraphic should be so that it is the same percentage of the maximum height
        float wallHeight = (elapsedTimePercent * maxBounds.y);
        // Step 3: Figure out the anchor point that should be at this height and set the position
        sf::Vector2f newAnchorPoint = sf::Vector2f(minAnchorPoint.x, minAnchorPoint.y-wallHeight);
        fireLayer1->getSprite().setPosition(firewallOffset+newAnchorPoint);
        fireLayer2->getSprite().setPosition(firewallOffset+newAnchorPoint);
        fireLayer3->getSprite().setPosition(firewallOffset+newAnchorPoint);
        // Step 4: Set the height of the wall
        //fireLayer1.setSize(sf::Vector2f(maxBounds.x, wallHeight));
    }
}

void Complication::FireWall::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(active) {
        Globals::game->renderWindow.setView(Globals::computerView);

        renderTarget.draw(*progressBar, states);
        renderTarget.draw(*fireLayer3, states);
        renderTarget.draw(*fireLayer2, states);
        renderTarget.draw(*fireLayer1, states);

        Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
    }
}

bool Complication::ComplicationFactories::generateFirewalls(std::list<Complication*> &complications, int jobInputs, int number, int maxLength, int minLength, float timeScale) {
    if(minLength > maxLength) return false;
    if(maxLength*number > jobInputs) return false;
    if(number == 0 || timeScale == 0) return false;
    
    for (int i=0; i<number; i++) {
        int numKeys = (rand() % (maxLength-minLength)+1) + minLength; 
        int complicationStartKeys = (i*maxLength) + maxLength-numKeys;
        float duration = float(numKeys/timeScale);
        float cooldownTime = duration/3.f;
        std::cout << "Firewall number " << i << ":: NumKeys: " << numKeys << " , Start Keys: " << complicationStartKeys << " , duration: " << duration << " , CooldownTime: " << cooldownTime << "\n";
        FireWall* firewall = new FireWall(numKeys, sf::seconds(duration), sf::seconds(cooldownTime), complicationStartKeys, 0.0);
        complications.push_back(dynamic_cast<Complication*>(firewall));

    }
    return true;
}