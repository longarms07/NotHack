#pragma once
#include <SFML/Graphics.hpp>

/**************
 TODO:
    - Make Textfield have bounds and an optional background (to show bounds)
***************/

class TextField : public sf::Drawable, public EventSystem::MouseDownObserver, public EventSystem::TextEnteredObserver, public EventSystem::KeyPressedObserver {
    private:
        sf::Text text;
        sf::RectangleShape background;
        bool focused;

    public:
        TextField(sf::Vector2f, sf::Vector2f, sf::Font&);

        bool isFocused();
        sf::String getText();

        /*sf::Drawable*/
        void draw(sf::RenderTarget&, sf::RenderStates) const;

        /*sf::Transformable... but not really (because I do not want to stub everything)*/
        void setPosition(float, float);

        /*EventSystem Observers*/
        void mouseDown(sf::Event::MouseButtonEvent);
        void textEntered(sf::Event::TextEvent);
        void keyPressed(sf::Event::KeyEvent);
};