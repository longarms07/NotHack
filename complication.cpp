#pragma once
#include <iostream>
#include "complication.hpp"
#include "globals.hpp"

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
    : fireLayer1(),
      fireLayer2(),
      fireLayer3(),
      barOffset(0.f, 80.f),
      firewallOffset(-10.f, 0.f)
{
    maxAnchorPoint = Globals::hackerWindow->getAnchorPoint();
    maxBounds = Globals::hackerWindow->getWidthHeight();
    minAnchorPoint = sf::Vector2f(maxAnchorPoint.x, maxAnchorPoint.y+maxBounds.y);
    
    fireLayer1.setPosition(minAnchorPoint);
    fireLayer1.setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    fireLayer1.setTexture(Globals::computerSpriteSheet);
    fireLayer1.setTextureRect(sf::IntRect(2, 7, 348, 326));
    
    fireLayer2.setPosition(minAnchorPoint);
    fireLayer2.setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    fireLayer2.setTexture(Globals::computerSpriteSheet);
    fireLayer2.setTextureRect(sf::IntRect(367, 26, 348, 326));
    
    fireLayer3.setPosition(minAnchorPoint);
    fireLayer3.setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    fireLayer3.setTexture(Globals::computerSpriteSheet);
    fireLayer3.setTextureRect(sf::IntRect(721, 16, 348, 326));
    
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
    
    progressBar = new ProgressBar(barOffset+minAnchorPoint, sf::Vector2f(maxBounds.x, 20), sf::Color::Blue, numTargetChars, "Firewall detected... hacking...", 14);
    Coolant::setFireWall(this);
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 1);
    std::cout << "The firewall has been created!\n";
}

Complication::FireWall::~FireWall() {
    delete progressBar;
    Coolant::setFireWall(NULL);
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}

void Complication::FireWall::startComplication() {
    active = true;
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
        else updateGraphics();
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
        fireLayer1.setPosition(firewallOffset+newAnchorPoint);
        fireLayer2.setPosition(firewallOffset+newAnchorPoint);
        fireLayer3.setPosition(firewallOffset+newAnchorPoint);
        // Step 4: Set the height of the wall
        //fireLayer1.setSize(sf::Vector2f(maxBounds.x, wallHeight));
    }
}

void Complication::FireWall::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(active) {
        Globals::game->renderWindow.setView(Globals::computerView);

        renderTarget.draw(fireLayer3, states);
        renderTarget.draw(fireLayer2, states);
        renderTarget.draw(fireLayer1, states);
        renderTarget.draw(*progressBar, states);

        Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
    }
}