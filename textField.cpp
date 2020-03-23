#include "textField.hpp"
#include <iostream>

TextField::TextField(sf::Vector2f position, sf::Vector2f widthHeight, const sf::Font& font)
    : background(widthHeight) {
    focused = false;

    background.setPosition(position.x, position.y);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x, position.y);
}

void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(text, states);
}

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

void TextField::textEntered(sf::Event::TextEvent event) {
    // std::cout << "Text entered event" << std::endl;
    const sf::String inputCharacter(event.unicode);
    if (focused) {
        text.setString(text.getString()+inputCharacter);
    }
}

void TextField::keyPressed(sf::Event::KeyEvent event) {
    if (focused) {
        switch (event.code) {
            case sf::Keyboard::Escape:
                focused = false;
                break;
            case sf::Keyboard::BackSpace:
            {
                sf::String currentString = text.getString();
                size_t size = currentString.getSize();
                if (size > 0) {
                    currentString.erase(size-1);
                    text.setString(currentString);
                }
                break;
            }
            case sf::Keyboard::Return:
                break;
        }
    }
}