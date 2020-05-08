#pragma once
#include "hackerText.hpp"
#include "globals.hpp"

HackerText::HackerText() 
    : text(){
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 2);
}

HackerText::~HackerText() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}


void HackerText::setString (const std::string &da_string){
    text.setString(da_string);
}

void HackerText::setFont (const sf::Font &da_font){
    text.setFont(da_font);
}

void HackerText::setCharacterSize (unsigned int size){
    text.setCharacterSize(size);
}

void HackerText::setPosition (float x, float y){
    text.setPosition(x,y);
}

void HackerText::setPosition (const sf::Vector2f &position){
    text.setPosition(position);
}




void HackerText::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const{
    Globals::game->renderWindow.setView(Globals::computerView);
        renderTarget.draw(text, states);
    Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
}