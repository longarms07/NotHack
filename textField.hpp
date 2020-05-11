#pragma once
#include <SFML/Graphics.hpp>

/*********************************
 * Class for text field (such as URL bar)
 *********************************/

class TextField : public sf::Drawable, public EventSystem::MouseDownObserver, public EventSystem::TextEnteredObserver, public EventSystem::KeyPressedObserver {
    private:
        sf::Text text; // Text being displayed
        sf::RectangleShape background; // Background for the field (shows bounds)
        bool focused; // Is the field currently receiving inputs?

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