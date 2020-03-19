#include "worldWideWeb.hpp"

WorldWideWeb::BrowserWindow::BrowserWindow(sf::Vector2f anchorPoint, sf::Vector2f widthHeight)
    : windowBackground()
{
    currentSite = 0;

    windowBackground.setPosition(anchorPoint);
    windowBackground.setSize(widthHeight);
    windowBackground.setFillColor(sf::Color::Green);
}

WorldWideWeb::BrowserWindow::~BrowserWindow() {
    delete currentSite;
}

void WorldWideWeb::BrowserWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(windowBackground, states);
}