#pragma once
#include "outro.hpp"
#include "globals.hpp"
#include "game.h"


/******************************************************************************
 * Outro Constructor -- Constructor for creating a new instance.              *
 ******************************************************************************/
Outro::Outro()
    :outroText(), outroSprite() {
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 3);
    outroText.setFont(Globals::defaultFont);
    outroText.setFillColor(sf::Color::Black);
    displayAccessFullGame();
}

/******************************************************************************
 * Outro Deonstructor -- Deonstructor for destroying an instance.             *
 ******************************************************************************/
Outro::~Outro() {
}

/******************************************************************************
 * update -- Called every frame. If the timer is active it increases it, and  *
 *      once the timer passes max time displays the next character of text on *
 *      screen if there is one, or calls the next state function if the state *
 *      calls for it.                                                         *
 * Parameters:                                                                *
 *      -deltaTime: the time since the last frame.                            *
 ******************************************************************************/
void Outro::update(sf::Time deltaTime) {
    if(timeActive) {
        timer+=deltaTime;
        if(timer >= maxTime) {
            if(!textQueue.empty()) { 
                // Display the next character of text
                outroText.setString(outroText.getString()+textQueue.front()[0]);
                textQueue.front() = textQueue.front().substr(1);
                if(textQueue.front().size() == 0) {
                    textQueue.pop_front();
                    outroText.setString(outroText.getString()+"\n");
                }
                if(textQueue.empty()) maxTime = sf::seconds(2.f); // Prepare to change states
                startTimer();
            }
            else {
                // Change the state of the game based on the current state.
                timeActive = false;
                maxTime = sf::seconds(2.f);
                switch(state) {
                    case hackerWindowBlueScreen:
                        displayFullBlueScreen();
                        break;
                    case fullBlueScreen:
                        displayFinalText();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

/******************************************************************************
 * next -- Transitions the outro into the next state based on the current one.*
 ******************************************************************************/
void Outro::next() {
    switch(state) {
        case accessFullGame:
            displayHackerWindowBlueScreen();
            break;
        case hackerWindowBlueScreen:
            break;
        case fullBlueScreen:
            displayFinalText();
            break;
        case done:
            break;
    }
}

/******************************************************************************
 * displayAccessFullGame -- Transitions to the first state, the fake victory  *
 *      screen. Sets the text and background sprite to fit where the          *
 *      HackerWindow is, and queues the victory message for display.          *
 ******************************************************************************/
void Outro::displayAccessFullGame() {
    //std::cout << "access full game..." << std::endl; // Debug
    maxTime = sf::seconds(0.05f);
    outroSprite.setPosition(Globals::hackerWindow->getAnchorPoint());
    outroSprite.setSize(Globals::hackerWindow->getWidthHeight());
    outroSprite.setFillColor(sf::Color::Green);
    outroText.setPosition(Globals::hackerWindow->getAnchorPoint());
    outroText.setCharacterSize(14);

    //Queue the message
    textQueue.push_back("Hack completed!\n\n");
    textQueue.push_back("Press the space key");
    textQueue.push_back("to access the full game.");
    startTimer();
}

/******************************************************************************
 * displayHackerWindowBlueScreen -- Transitions to the second state, the      *
 *      HackerWindow Blue Screen of death and queues the victory message for  *
 *      display.                                                              *
 ******************************************************************************/
void Outro::displayHackerWindowBlueScreen() {
    //std::cout << "Displaying small Blue Screen..." << std::endl; // Debug
    state = hackerWindowBlueScreen;
    textQueue.clear();
    outroText.setString("");
    outroSprite.setFillColor(sf::Color::Blue);
    maxTime = sf::seconds(0.05f);

    //Queue the message
    textQueue.push_back("Segmentation Fault (core dumped)!\n");
    textQueue.push_back("Null Pointer Exception when accessing\n");
    textQueue.push_back("'NotHack_Full_Game.'\n");
    textQueue.push_back("Full Game Not Found!");
    startTimer();
}

/******************************************************************************
 * displayFullWindowBlueScreen -- Transitions to the third state, the Game    *
 *      Window Blue Screen of death, and resizes the text and sprite to fill  *
 *      the game window.                                                      *
 ******************************************************************************/
void Outro::displayFullBlueScreen() {
    //std::cout << "Displaying Full Blue Screen..." << std::endl; // Debug
    state = fullBlueScreen;
    outroSprite.setPosition(sf::Vector2f(0.f,0.f));
    sf::Vector2u windowSize = Globals::game->renderWindow.getSize();
    outroSprite.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    outroText.setPosition(sf::Vector2f(0.f,0.f));
    outroText.setCharacterSize(28);
    startTimer();
}

/******************************************************************************
 * displayAccessFullGame -- Transitions to the fourth state, the "Thank you   *
 *      for playing," and queues the message.                                 * 
 ******************************************************************************/
void Outro::displayFinalText() {
    //std::cout << "Displaying final text..." << std::endl; // Debug
    state = done; 
    maxTime = sf::seconds(0.05f);
    outroText.setString("");
    textQueue.clear();

    //Queue the message
    textQueue.push_back("Well, we tried to warn you not to complete the hack!\n");
    textQueue.push_back("The full game is not yet ready.\n");
    textQueue.push_back("But we promise that what you have experienced so far\n");
    textQueue.push_back("has just been the easy part...\n\n");
    textQueue.push_back("Thank you for playing our proof of concept for\n");
    textQueue.push_back("'NotHack: Weaponized Polymorphic Methods'!");
    startTimer();
}

/******************************************************************************
 * startTimer -- Resets the timer.                                            * 
 ******************************************************************************/
void Outro::startTimer() {
    timer = sf::Time::Zero;
    timeActive = true;
}

/******************************************************************************
 * draw -- Renders the Cooler graphics.                                       *
 * Overrides the Virtual function from Drawable.                              *
 ******************************************************************************/
void Outro::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(state == accessFullGame || state == hackerWindowBlueScreen)
        Globals::game->renderWindow.setView(Globals::computerView);

    renderTarget.draw(outroSprite, states);
    renderTarget.draw(outroText, states);
    
    if(state == accessFullGame || state == hackerWindowBlueScreen)
        Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
}