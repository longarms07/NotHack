#pragma once
#include <iostream>
#include "complication.hpp"
#include "globals.hpp"
#include "spriteAnimations.hpp"

/*****************************************************
 ***********General Complication Functions************
 *****************************************************/

/*****************************************************
 * getNumberKeysRequired -- Getter method for the    *
 *     key inputs needed to defeat the complication. * 
 * Returns:                                          *
 *     An integer representing the amount of key     *
 *     inputs needed to defeat the complication.     *    
 *****************************************************/
int Complication::Complication::getNumberKeysRequired() {
    return numKeysReq;
}

/*****************************************************
 * getPenaltyValue -- Getter method for the          *
 *     punishment for failing to defeat the          *
 *     complication.                                 * 
 * Returns:                                          *
 *     An double representing the monetary penalty   *
 *     inflicted on the player if the complication   *
 *     completes successfully.                       *    
 *****************************************************/
double Complication::Complication::getPenaltyValue() {
    return penalty;
}

/*****************************************************
 * getEndData -- Getter method for the    *
 *     complication's current endData.               * 
 * Returns:                                          *
 *     An endData struct.                            *
 *     'ended' is true after the complication is     *
 *     defeated or completes, false otherwise.       *
 *     'defeated' is true if the player defeats      *
 *     the complication.                             *     
 *****************************************************/
Complication::endData Complication::Complication::getEndData() { 
    return endingData;
}

/*****************************************************
 * isActive -- Getter method for whether or not the  *
 *     complication has been activated.              * 
 * Returns:                                          *
 *    -True if the complication has been activated   *
 *      and is runninng.                             *     
 *    -False if the complication has not been        *
 *      activated or if it has ended.                *
 *****************************************************/
bool Complication::Complication::isActive() {
    return active;
}



/*****************************************************
 *****************Firewall Functions******************
 *****************************************************/



/*****************************************************
 * Firewall Constructor -- Constructor for creating  *
 *     instances of Firewall Complication            * 
 * Parameters:                                       *
 *    -targetChars: An integer representing the      *
 *      number of key inputs needed to defeat the    *
 *      firewall.                                    *
 *    -maxTime: The amount of seconds the Firewall   *
 *      is active before completing successfully.    *
 *    -coolTime: The amount of time removed from the *
 *      Firewall's timer when Coolant is used on it. *
 *      (How much coolant extends the firewall's     *
 *      active time).                                *
 *    -activationKeys: How many key inputs the       *
 *      player must enter before the Firewall can    *
 *      activate.                                    *
 *    -penaltyAmount: The amount of the penalty if   *
 *      the firewall completes successfully.         * 
 *****************************************************/
Complication::FireWall::FireWall(int targetChars, sf::Time maxTime, sf::Time coolTime, int activationKeys, double penaltyAmount)
    : barOffset(0.f, -165.f),
      firewallOffset(-10.f, 0.f)
{
    // Initializing the bounds at which the Firwall is drawn
    maxAnchorPoint = Globals::hackerWindow->getAnchorPoint();
    maxBounds = Globals::hackerWindow->getWidthHeight();
    minAnchorPoint = sf::Vector2f(maxAnchorPoint.x, maxAnchorPoint.y+maxBounds.y);
    
    // Initializng the sprites for the fire animation
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
    
    // Setting up the time variables
    maximumTime = maxTime;
    coolantTime = coolTime;
    elapsedTime = sf::Time::Zero;

    // Setting up the key input variables
    numTargetChars = targetChars;
    numEnteredChars = 0;
    numKeysReq = activationKeys;

    // Setting up the state variables. Initializes inactive. 
    active = false;
    endingData.defeated = false;
    endingData.ended = false;
    penalty = penaltyAmount;
    
    // Setting up the progress bar
    progressBar = new ProgressBar(barOffset+minAnchorPoint, sf::Vector2f(maxBounds.x, 20), sf::Color::Blue, numTargetChars, "Firewall detected... coding anti-fire...", 14);
    
    //Registering the Firewall as a drawable
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 1);
    
    //std::cout << "The firewall has been created!\n"; // Debug
}

/*****************************************************
 * Firewall Deconstructor -- delete's the Firewall's *
 *     member pointers and destroys the firewall.    * 
 *****************************************************/
Complication::FireWall::~FireWall() {
    // Delete the pointers instantiated with 'new'
    delete progressBar;
    delete fireLayer1;
    delete fireLayer2;
    delete fireLayer3;

    //Unregister the Firewall from the Coolant and Render System
    Coolant::setFireWall(NULL);
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}

/*****************************************************
 * startComplication -- Activates the Firewall       *
 * Overrides the Virtual function from Complication  *
 *****************************************************/
void Complication::FireWall::startComplication() {
    active = true; // activate the firewall
    Coolant::setFireWall(this); // Set this as the active Firewall for coolant to target
    updateGraphics(); // Begin drawing the firewall
}

/*****************************************************
 * startComplication -- Ends the Firewall.           *
 * Parameters:                                       *
 *      -Defeated: True if the player defeated the   *
 *       Firewall, false if not.                     *
 * Overrides the Virtual function from Complication  *
 *****************************************************/
void Complication::FireWall::endComplication(bool defeated) {
    active = false; // Deactivate the Firewall
    // Set the endData struct
    endingData.defeated = defeated;
    endingData.ended = true;

    // Messages to denote how the Firewall ended.
    // TODO: Put these messages on the game screen.
    if (defeated) std::cout << "The firewall has been defeated!\n";
    else std::cout << "The firewall has melted your computer!\n";
}

/*****************************************************
 * keyPressed -- Increments the number of key inputs *
 *      registered and checks if the Firewall has    *
 *      been defeated.                               *
 * Overrides the Virtual function from Complication  *
 *****************************************************/
void Complication::FireWall::keyPressed() {
    if(active) {
        numEnteredChars++; // Increment the number of recieved key inputs
        //std::cout << "The firewall has recieved a char!\n"; // Debug
        progressBar->incrementProgress(1); // Update the Progress Bar
        // End the Firewall if enough keys have been entered to defeat it
        if (numEnteredChars >= numTargetChars) endComplication(true); 
    }
}

/*****************************************************
 * Update -- Called every frame- checks if enough    *
 *      time has passed for the firewall to complete.*
 * Overrides the Virtual function from Complication  *
 *****************************************************/
void Complication::FireWall::update(sf::Time deltaTime) {
    if(active) {
        elapsedTime+= deltaTime; // Updates the timer
        //std::cout << "The firewall has " << (maximumTime.asSeconds()-elapsedTime.asSeconds()) << " seconds left!\n"; // Debug
        if (elapsedTime >= maximumTime) endComplication(false); // If the maximum time has passed complete the complication.
        else { // Else update the Firewall Graphics.
            updateGraphics();
            fireLayer1->update(deltaTime);
            fireLayer2->update(deltaTime);
            fireLayer3->update(deltaTime);
        }
    }
}

/*****************************************************
 * coolantApplied -- Removes the coolantTime from    *
 *      the timer.                                   *
 *****************************************************/
void Complication::FireWall::coolantApplied() {
    if(active) {
        elapsedTime-= coolantTime;
        if(elapsedTime < sf::Time::Zero) elapsedTime = sf::Time::Zero; // Timer cannot go below 0
        updateGraphics();
    }
}

/*****************************************************
 * updateGraphics -- Updates the Firewall graphics   *
 *      to have a height relative to the time that   *
 *      the firewall has been active. It grows       *
 *      larger the closer it gets to completing.     *
 *****************************************************/
void Complication::FireWall::updateGraphics() {
    if(active) {
        /* Step 1: Get the percentage of the time that is left. 
           This is done by dividing the elapsed time by the maximum time.*/
        float elapsedTimePercent = elapsedTime.asSeconds() / maximumTime.asSeconds();
        // Step 2: Calculate the height the wallGraphic should be so that it is the same percentage of the maximum height
        float wallHeight = (elapsedTimePercent * maxBounds.y);
        // Step 3: Figure out the anchor point that should be at this height and set the position
        sf::Vector2f newAnchorPoint = sf::Vector2f(minAnchorPoint.x, minAnchorPoint.y-wallHeight);
        // Step 4: Set the height of the wall
        fireLayer1->getSprite().setPosition(firewallOffset+newAnchorPoint);
        fireLayer2->getSprite().setPosition(firewallOffset+newAnchorPoint);
        fireLayer3->getSprite().setPosition(firewallOffset+newAnchorPoint);
    }
}

/*****************************************************
 * draw -- Renders the Firewall graphics.            *
 * Overrides the Virtual function from Drawable.     *
 *****************************************************/
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



/*****************************************************
 ***********Complication Factory Functions************
 *****************************************************/

/*****************************************************
 * generateFirewalls -- Generates a list of          *
 *      Firewalls to be the complications for a job. *
 * Paramters:                                        *
 *      -complications: A reference to a job's list  *
 *        of complications. Complications are added  *
 *        to the list in-place, so the job can       *
 *        retrieve them.                             *
 *      -jobInputs: The total integer amount of key  *
 *          inputs in the job calling this method.   *
 *      -number: The integer number of Firewalls to  *
 *          create.                                  *
 *      -maxLength: The integer representing the     *
 *        maximum number of key inputs required to   *
 *      defeat a firewall.                           * 
 *      -minLength: The integer representing the     *
 *         minimum number of key inputs required to  *
 *         defeat a firewall. Must be < maxLength.   * 
 *      -timeScale: The float used to determine the  *
 *         amount of seconds per key the player is   *
 *         expected to input. (keys/timeScale).      *
 *         WARNING: Must be !=0.                     *
 * Returns:                                          *
 *     -True if the complication list is populated.  *
 *     -False if the list can not be populated.      *
 *****************************************************/
bool Complication::ComplicationFactories::generateFirewalls(std::list<Complication*> &complications, int jobInputs, int number, int maxLength, int minLength, float timeScale) {
    // Safety check the parameters to make sure generating firewalls is possible
    if(minLength > maxLength) return false;
    if(maxLength*number > jobInputs) return false;
    if(number == 0 || timeScale == 0) return false;
    
    //Generate the Firewalls
    for (int i=0; i<number; i++) {
        // Determine they key input variables of the firewall
        int numKeys = (rand() % (maxLength-minLength)+1) + minLength;   
        int complicationStartKeys = (i*maxLength) + maxLength-numKeys;
        // Determine the time variables of the firewall
        float duration = float(numKeys/timeScale);
        float cooldownTime = duration/3.f;
        //std::cout << "Firewall number " << i << ":: NumKeys: " << numKeys << " , Start Keys: " << complicationStartKeys << " , duration: " << duration << " , CooldownTime: " << cooldownTime << "\n"; // Debug
        
        // Generate the firewall and add it to the list.
        FireWall* firewall = new FireWall(numKeys, sf::seconds(duration), sf::seconds(cooldownTime), complicationStartKeys, 0.0);
        complications.push_back(dynamic_cast<Complication*>(firewall));
    }
    return true;
}