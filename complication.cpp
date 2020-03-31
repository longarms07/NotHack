#pragma once
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
    : wallGraphic() {
    maxAnchorPoint = Globals::hackerWindow->getAnchorPoint();
    maxBounds = Globals::hackerWindow->getWidthHeight();
    minAnchorPoint = sf::Vector2f(maxAnchorPoint.x, maxAnchorPoint.y+maxBounds.y);
    wallGraphic.setPosition(minAnchorPoint);
    wallGraphic.setSize(sf::Vector2f(maxBounds.x, 0.f));
    wallGraphic.setFillColor(sf::Color::Red);
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
    progressBar = new ProgressBar(minAnchorPoint, sf::Vector2f(maxBounds.x, 30), sf::Color::Green, numTargetChars, "Breaking Firewall", 20);
    Coolant::setFireWall(this);
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this);
    std::cout << "The firewall has been created!\n";
}

Complication::FireWall::~FireWall() {
    delete progressBar;
    Coolant::setFireWall(NULL);
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}

void Complication::FireWall::startComplication() {
    active = true;
    updateWallGraphic();
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
        else updateWallGraphic();
    }
}

void Complication::FireWall::coolantApplied() {
    if(active) {
        elapsedTime-= coolantTime;
        if(elapsedTime < sf::Time::Zero) elapsedTime = sf::Time::Zero;
        updateWallGraphic();
    }
}

void Complication::FireWall::updateWallGraphic() {
    if(active) {
        // Step 1: Get the percentage of the time that is left. 
        // This is done by dividing the elapsed time by the maximum time.
        float elapsedTimePercent = elapsedTime.asSeconds() / maximumTime.asSeconds();
        //if(elapsedTimePercent > 1) elapsedTimePercent == 1;
        // Step 2: Calculate the height the wallGraphic should be so that it is the same percentage of the maximum height
        float wallHeight = (elapsedTimePercent * maxBounds.y);
        // Step 3: Figure out the anchor point that should be at this height and set the position
        sf::Vector2f newAnchorPoint = sf::Vector2f(minAnchorPoint.x, minAnchorPoint.y-wallHeight);
        wallGraphic.setPosition(newAnchorPoint);
        // Step 4: Set the height of the wall
        wallGraphic.setSize(sf::Vector2f(maxBounds.x, wallHeight));
    }
}

void Complication::FireWall::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(active) {
        renderTarget.draw(wallGraphic, states);
        renderTarget.draw(*progressBar, states);
    }
}