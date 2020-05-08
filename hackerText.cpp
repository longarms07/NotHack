#pragma once
#include "hackerText.hpp"
#include "globals.hpp"

/******************************************************************************
 * HackerText Constructor -- Constructor for creating a new instance.         * 
 ******************************************************************************/
HackerText::HackerText() 
    : text(){
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this, 2);
}

/******************************************************************************
 * HackerText Deonstructor -- Deconstructor for destroying an instance.       * 
 ******************************************************************************/
HackerText::~HackerText() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}

/******************************************************************************
 * setString -- calls the setString method of the member text object.         * 
 * Parameters:                                                                *
 *      da_string: A reference to the string for the text object to display.  *
 ******************************************************************************/
void HackerText::setString (const std::string &da_string){
    text.setString(da_string);
}

/******************************************************************************
 * setFont -- calls the setFont method of the member text object.             * 
 * Parameters:                                                                *
 *      da_font: A reference to the font for the text object to utilize.      *
 ******************************************************************************/
void HackerText::setFont (const sf::Font &da_font){
    text.setFont(da_font);
}

/******************************************************************************
 * setCharacterSize -- calls the setCharacterSize method of the member text   *
 *      object.                                                               * 
 * Parameters:                                                                *
 *      size: A reference to the int for the text object's font size.         *
 ******************************************************************************/
void HackerText::setCharacterSize (unsigned int size){
    text.setCharacterSize(size);
}

/******************************************************************************
 * setPosition -- calls the setPosition method of the member text object.     * 
 * Parameters:                                                                *
 *      x: A float representing the x position for the text object.           *
 *      y: A float representing the y position for the text object.           *
 ******************************************************************************/
void HackerText::setPosition (float x, float y){
    text.setPosition(x,y);
}

/******************************************************************************
 * setPosition -- calls the setPosition method of the member text object.     * 
 * Parameters:                                                                *
 *      position: a reference to a Vector2 Float to use for the text object's *
 *          position.                                                         *
 ******************************************************************************/
void HackerText::setPosition (const sf::Vector2f &position){
    text.setPosition(position);
}




void HackerText::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const{
    Globals::game->renderWindow.setView(Globals::computerView);
        renderTarget.draw(text, states);
    Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
}