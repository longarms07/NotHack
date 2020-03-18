#include "fireWall.h"
#include "hackerWindow.h"

FireWall::FireWall(HackerWindow* parent, int targetChars, sf::Time maxTime, sf::Time coolTime)
    : wallGraphic() {
    parentHackerWindow = parent;
    maxAnchorPoint = parent->getAnchorPoint();
    maxBounds = parent->getWidthHeight();
    minAnchorPoint = sf::Vector2f(maxAnchorPoint.x, maxAnchorPoint.y+maxBounds.y);
    wallGraphic.setPosition(minAnchorPoint);
    wallGraphic.setSize(sf::Vector2f(maxBounds.x, 0.f));
    wallGraphic.setFillColor(sf::Color::Red);
    maximumTime = maxTime;
    coolantTime = coolTime;
    elapsedTime = sf::Time::Zero;
    numTargetChars = targetChars;
    numEnteredChars = 0;
    std::cout << "The firewall has been created!\n";
}

void FireWall::charEntered() {
    numEnteredChars++;
    std::cout << "The firewall has recieved a char!\n";
    if (numEnteredChars >= numTargetChars) endFireWall();
}

void FireWall::update(sf::Time deltaTime) {
    if(elapsedTime < maximumTime) {
        elapsedTime+= deltaTime;
        //std::cout << "The firewall has " << (maximumTime.asSeconds()-elapsedTime.asSeconds()) << " seconds left!\n";
        if (elapsedTime >= maximumTime) endJob();
        else updateWallGraphic();
    }
}

void FireWall::coolantApplied() {
    elapsedTime-= coolantTime;
    if(elapsedTime < sf::Time::Zero) elapsedTime = sf::Time::Zero;
    updateWallGraphic();
}

void FireWall::endFireWall() {
    // Stubbed
    std::cout << "FireWall has been defeated!\n";
    parentHackerWindow->derefFireWall();
    delete this;
}

void FireWall::endJob() {
    // Stubbed
    std::cout << "Oh noes! The FireWall has melted your computer!\n";
    //parentHackerWindow->derefFireWall();
}

void FireWall::updateWallGraphic() {
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

void FireWall::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    renderTarget.draw(wallGraphic, states);
}