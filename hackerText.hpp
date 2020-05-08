#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "registerable.hpp"

class HackerText : public sf::Drawable{
    public:
        HackerText();
        ~HackerText();

        void setString (const std::string &string);
        void setFont (const sf::Font &font);
        void setCharacterSize (unsigned int size);
        void setPosition (float x, float y);
        void setPosition (const sf::Vector2f &position);

    private:
       sf::Text text;
       virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const override; 
};