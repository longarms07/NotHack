#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list> 

class HackerWindow : public sf::Drawable {
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
        void updateHackerText();
        void update(sf::Time deltaTime); 
        bool contains(sf::Vector2f pos);
        void updateList(char c);

    private:
        sf::Font hackerFont; // Font of the text
        sf::Text hackerText; // Textbox that the text is stored within. 
        sf::RectangleShape hackerScreen; // The background screen of the window
        sf::Vector2f anchorPoint; // Top-left pixel of the hacker window
        sf::Vector2f widthHeight; // Width and height of the window
        sf::Color textColor; // Color of the text
        std::list<std::string> displayedCode = { "" };
        const int displayedCodeSize = 5;

        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};