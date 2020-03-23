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
        TextField(sf::Vector2f, sf::Vector2f, const sf::Font&);

        /*sf::Drawable*/
        void draw(sf::RenderTarget&, sf::RenderStates) const;

        /*EventSystem Observers*/
        void mouseDown(sf::Event::MouseButtonEvent);
        void textEntered(sf::Event::TextEvent);
        void keyPressed(sf::Event::KeyEvent);
};