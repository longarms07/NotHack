#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "registerable.hpp"


/******************************************************************************
 * HackerText:                                                                *
 *      -A data structure that allows the HackerWindow's text to be drawn on  *
 *       a seperate render layer from the HackerWindow.                       *
 *      -A derived class of Drawable                                          *
 * Visual:                                                                    *
 *      -A standard SFML text object.                                         *
 ******************************************************************************/
class HackerText : public sf::Drawable{
    public:
        HackerText();
        ~HackerText();

        // The following methods call the method of the same name in the sf::Text
        void setString (const std::string &string);
        void setFont (const sf::Font &font);
        void setCharacterSize (unsigned int size);
        void setPosition (float x, float y);
        void setPosition (const sf::Vector2f &position);

    private:
       sf::Text text;
       virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const override; 
};