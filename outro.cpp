#pragma once
#include "outro.hpp"
#include "globals.hpp"
#include "game.h"

Outro::Outro()
    :outroText(), outroSprite() {
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 3);
    outroText.setFont(Globals::defaultFont);
    outroText.setFillColor(sf::Color::White);
    displayAccessFullGame();
}

Outro::~Outro() {
}

void Outro::update(sf::Time deltaTime) {
    if(timeActive) {
        timer+=deltaTime;
        if(timer >= maxTime) {
            if(!textQueue.empty()) {
                //std::string text = outroText.getString()+"\n"+textQueue.front();
                outroText.setString(outroText.getString()+textQueue.front()[0]);
                textQueue.front() = textQueue.front().substr(1);
                //std::cout << text << std::endl;
                if(textQueue.front().size() == 0) {
                    textQueue.pop_front();
                    outroText.setString(outroText.getString()+"\n");
                }
                if(textQueue.empty()) maxTime = sf::seconds(2.f);
                startTimer();
            }
            else {
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

void Outro::displayAccessFullGame() {
    std::cout << "access full game..." << std::endl;
    maxTime = sf::seconds(0.05f);
    outroSprite.setPosition(Globals::hackerWindow->getAnchorPoint());
    outroSprite.setSize(Globals::hackerWindow->getWidthHeight());
    outroSprite.setFillColor(sf::Color::Green);
    outroText.setPosition(Globals::hackerWindow->getAnchorPoint());
    outroText.setCharacterSize(14);
    textQueue.push_back("Hack completed!\n\n");
    textQueue.push_back("Press the space key");
    textQueue.push_back("to access the full game.");
    startTimer();
}

void Outro::displayHackerWindowBlueScreen() {
    std::cout << "Displaying small Blue Screen..." << std::endl;
    state = hackerWindowBlueScreen;
    textQueue.clear();
    outroText.setString("");
    outroSprite.setFillColor(sf::Color::Blue);
    maxTime = sf::seconds(0.05f);
    textQueue.push_back("Segmentation Fault (core dumped)!\n");
    textQueue.push_back("Null Pointer Exception when accessing\n");
    textQueue.push_back("'NotHack_Full_Game.'\n");
    textQueue.push_back("Full Game Not Found!");
    startTimer();
}

void Outro::displayFullBlueScreen() {
    std::cout << "Displaying Full Blue Screen..." << std::endl;
    state = fullBlueScreen;
    outroSprite.setPosition(sf::Vector2f(0.f,0.f));
    sf::Vector2u windowSize = Globals::game->renderWindow.getSize();
    outroSprite.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    outroText.setPosition(sf::Vector2f(0.f,0.f));
    outroText.setCharacterSize(28);
    startTimer();
}

void Outro::displayFinalText() {
    std::cout << "Displaying final text..." << std::endl;
    state = done; 
    maxTime = sf::seconds(0.05f);
    outroText.setString("");
    textQueue.clear();
    textQueue.push_back("Well, we tried to warn you not to complete the hack!\n");
    textQueue.push_back("The full game is not yet ready.\n");
    textQueue.push_back("But we promise that what you have experienced so far\n");
    textQueue.push_back("has just been the easy part...\n\n");
    textQueue.push_back("Thank you for playing our proof of concept for\n");
    textQueue.push_back("'NotHack: Weaponized Polymorphic Methods'!");
    startTimer();
}

void Outro::startTimer() {
    timer = sf::Time::Zero;
    timeActive = true;
}


void Outro::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    if(state == accessFullGame || state == hackerWindowBlueScreen)
        Globals::game->renderWindow.setView(Globals::computerView);

    renderTarget.draw(outroSprite, states);
    renderTarget.draw(outroText, states);
    
    if(state == accessFullGame || state == hackerWindowBlueScreen)
        Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
}