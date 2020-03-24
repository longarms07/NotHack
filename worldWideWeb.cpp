#include "worldWideWeb.hpp"
#include "eventSystem.hpp"
#include <iostream>
#include <string>

WorldWideWeb::BrowserWindow::BrowserWindow(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Font& font)
    : windowBackground()
{

    windowBackground.setPosition(anchorPoint);
    windowBackground.setSize(widthHeight);
    windowBackground.setFillColor(sf::Color(85, 85, 85));

    urlBar = new URLBar(font);
    currentSite = WorldWideWeb::Sites::Red::getInstance();

    dragging = false;
}

WorldWideWeb::BrowserWindow::~BrowserWindow() {
    delete urlBar;
}

void WorldWideWeb::BrowserWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(windowBackground, states);

    target.draw(*urlBar, windowBackground.getTransform());
    target.draw(*currentSite, windowBackground.getTransform());
}

void WorldWideWeb::BrowserWindow::mouseMove(sf::Event::MouseMoveEvent event) {
    if (dragging) {
        sf::Vector2f eventLocation(event.x, event.y);
        windowBackground.setPosition(eventLocation - mouseOffsetFromOrigin);
    }
}

void WorldWideWeb::BrowserWindow::mouseDown(sf::Event::MouseButtonEvent event) {
    sf::Vector2f eventLocation(event.x, event.y);

    if (windowBackground.getGlobalBounds().contains(eventLocation)) {
        // std::cout << "Mouse down in bounds" << std::endl;
        mouseOffsetFromOrigin = eventLocation - windowBackground.getPosition();
        dragging = true;
    } else {
        // std::cout << "Mouse down outside bounds" << std::endl;
    }
}

void WorldWideWeb::BrowserWindow::keyPressed(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Return && urlBar->textField.isFocused()) {
        std::string comparableString = static_cast<std::string>(urlBar->textField.getText());
        if (comparableString == "red") {
            std::cout << "red found!" << std::endl;
            currentSite = WorldWideWeb::Sites::Red::getInstance();
        }
        if (comparableString == "blue") {
            std::cout << "blue found!" << std::endl;
            currentSite = WorldWideWeb::Sites::Blue::getInstance();
        }
    }
}

void WorldWideWeb::BrowserWindow::mouseUp(sf::Event::MouseButtonEvent event) {
    // std::cout << "Mouse up event" << std::endl;
    dragging = false;
}

WorldWideWeb::URLBar::URLBar(sf::Font& font)
    : textField(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 50.f), font)
{ }

void WorldWideWeb::URLBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(textField, states);
}

WorldWideWeb::Sites::Red::Red()
    : background()
{
    background.setPosition(sf::Vector2f(0.f, 100.f));
    background.setSize(sf::Vector2f(300.f, 200.f));
    background.setFillColor(sf::Color::Red);
}

void* WorldWideWeb::Sites::Red::operator new(size_t size) {
    return malloc(size);
}

void WorldWideWeb::Sites::Red::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
}

WorldWideWeb::Sites::Blue::Blue()
    : background()
{
    background.setPosition(sf::Vector2f(0.f, 100.f));
    background.setSize(sf::Vector2f(300.f, 200.f));
    background.setFillColor(sf::Color::Blue);
}

void* WorldWideWeb::Sites::Blue::operator new(size_t size) {
    return malloc(size);
}

void WorldWideWeb::Sites::Blue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
}