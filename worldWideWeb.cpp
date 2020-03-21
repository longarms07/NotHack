#include "worldWideWeb.hpp"
#include "eventSystem.hpp"
#include <iostream>

WorldWideWeb::BrowserWindow::BrowserWindow(sf::Vector2f anchorPoint, sf::Vector2f widthHeight)
    : windowBackground()
{
    currentSite = 0;

    windowBackground.setPosition(anchorPoint);
    windowBackground.setSize(widthHeight);
    windowBackground.setFillColor(sf::Color(85, 85, 85));

    dragging = false;
}

WorldWideWeb::BrowserWindow::~BrowserWindow() {
    delete currentSite;
}

void WorldWideWeb::BrowserWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(windowBackground, states);
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
        std::cout << "Mouse down in bounds" << std::endl;
        mouseOffsetFromOrigin = eventLocation - windowBackground.getPosition();
        dragging = true;
    } else {
        std::cout << "Mouse down outside bounds" << std::endl;
    }
}

void WorldWideWeb::BrowserWindow::mouseUp(sf::Event::MouseButtonEvent event) {
    std::cout << "Mouse up event" << std::endl;
    dragging = false;
}