#include "textField.hpp"
#include <iostream>


/*******************
 * Parameters:
 *  - sf::Vector2f position: screen coordinates to place the TextField
 *  - sf::Vector2f weidthHeight: dimensions of the TextField
 *  - sf::Font& font: Reference to font that will be used for the text
 *******************/
TextField::TextField(sf::Vector2f position, sf::Vector2f widthHeight, sf::Font& font)
    : background(widthHeight),
      EventSystem::MouseDownObserver(false),
      EventSystem::TextEnteredObserver(false),
      EventSystem::KeyPressedObserver(false)
{
    focused = false;

    background.setPosition(position.x, position.y);

    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x, position.y);
}

// Is the TextField current receiving inputs?
bool TextField::isFocused() {
    return focused;
}

// Returns the text currently being displayed
sf::String TextField::getText() {
    return text.getString();
}

/********************
 * sf:Drawable draw
 *
 * Parameters:
 *  - sf::RenderTarget& target: Target to draw object on
 *  - sf::RenderStates states: Extra information (ex. transformations) for drawing
 ********************/
void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(text, states);
}

// Set the screen position of the object
void TextField::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x, y);
}

/***************************
 * Event handling functions
 ***************************/


/***********************
 * If the mouse was clicked inside the bounds, put the TextField in focus
 * Otherwise, unfocus it
 ***********************/
void TextField::mouseDown(sf::Event::MouseButtonEvent event) {
    sf::Vector2f eventPosition(event.x, event.y);

    if (background.getGlobalBounds().contains(eventPosition)) {
        // std::cout << "It's time to type" << std::endl;
        focused = true;
    } else {
        // std::cout << "Clicked outside text bounds" << std::endl;
        focused = false;
    }
}

/************************
 * If the TextField is in focus,
 * add the text to the display
 ************************/
void TextField::textEntered(sf::Event::TextEvent event) {
    // std::cout << "Text entered event" << std::endl;
    const sf::String inputCharacter(event.unicode);
    if (focused) {
        text.setString(text.getString()+inputCharacter);
    }
}

/*************************
 * If the escape key was pressed, unfocus the TextField
 * If the backsapce key was pressed, remove the previous character
 *************************/
void TextField::keyPressed(sf::Event::KeyEvent event) {
    if (focused) {
        switch (event.code) {
            case sf::Keyboard::Escape:
                focused = false;
                break;
            case sf::Keyboard::BackSpace:
            { // Brackets used to add scope to local variable
                sf::String currentString = text.getString();
                size_t size = currentString.getSize();
                if (size > 0) {
                    currentString.erase(size-1);
                    text.setString(currentString);
                }
                break;
            }
        }
    }
}
