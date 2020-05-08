#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "registerable.hpp"
#include "hackerText.hpp"


/******************************************************************************
 * HackerWindow:                                                              *
 *      -The in-game computer's "display" during its in-job state.            *
 *       Text appears 1 character at a time as the user types, and scrolls up.*
 *      -A derived class of Drawable, Registerable.                           *
 * Visual:                                                                    *
 *      -A rectangular computer screen with text.                             *
 ******************************************************************************/
class HackerWindow : public sf::Drawable, public Registerable {
    public:
        HackerWindow(sf::Vector2f anchorPt, sf::Vector2f wH, sf::Font& font, const sf::Color& color);
        HackerWindow(float anchorPointX, float anchorPointY, float width, float height, sf::Font& font, const sf::Color& color);
        sf::Vector2f getAnchorPoint(); 
        sf::Vector2f getWidthHeight();
        sf::Font getFont();
        sf::Color getTextColor();
        void setAnchorPoint(sf::Vector2f anchorPt);
        void setAnchorPoint(float anchorPointX, float anchorPointY);
        void setWidthHeight(sf::Vector2f wH);
        void setWidthHeight(float width, float height);
        void setFont(sf::Font& font);
        void setTextColor(const sf::Color& color);
        void updateHackerText(); // Updates the text currently being displayed on the HackerScreen
        void clear();
        void update(sf::Time deltaTime); 
        bool contains(sf::Vector2f pos); // Returns whether or not the input position is within the Hackerwindow space
        void updateList(char c); // Updates the "displayedCode" list with the next character

        /*Registerable*/
        void activate(); // Subscribes the HackerWindow to the Render System
        void deactivate(); // Unsubscribes the HackerWindow from the Render System

    private:

        sf::Font hackerFont; // Font of the text
        HackerText hackerText; // Textbox that the text is stored within.
        sf::Sprite hackerScreen; // The background screen of the window
        
        sf::Vector2f anchorPoint; // Top-left pixel of the hacker window
        sf::Vector2f widthHeight; // Width and height of the view

        sf::Vector2f textOffset;
        
        sf::Color textColor; // Color of the text
        std::list<std::string> displayedCode = { "" }; // The list of text that is displayed on the screen.
        const int displayedCodeSize = 8;

        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};



