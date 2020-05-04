#include "hackerWindow.h"
#include <iostream>

HackerWindow::HackerWindow(sf::Vector2f anchorPt, sf::Vector2f wH, sf::Font& font, const sf::Color& color)
    : hackerText(), 
      hackerScreen(),
      textOffset(9.f, 38.f)
{
    anchorPoint = anchorPt;
    widthHeight = wH;
    hackerFont = font;
    textColor = color;

    hackerText.setFont(hackerFont);
    hackerText.setCharacterSize(14);
    hackerText.setString("Testing One Too Three");
    hackerText.setPosition(textOffset+anchorPoint);

    hackerScreen.setTexture(Globals::computerSpriteSheet);
    hackerScreen.setTextureRect(sf::IntRect(979, 783, 312, 237));
    hackerScreen.setScale(sf::Vector2f(0.8f, 0.8f)); // TODO: Un-hardcode
    hackerScreen.setPosition(anchorPoint);

    
    // hackerScreen.setFillColor(sf::Color::Green);
}

HackerWindow::HackerWindow(float anchorPointX, float anchorPointY, float width, float height, sf::Font& font, const sf::Color& color)
    : HackerWindow(sf::Vector2f(anchorPointX, anchorPointY), sf::Vector2f(width, height), font, color)
{ }

sf::Vector2f HackerWindow::getAnchorPoint() {
    return anchorPoint;
}

void HackerWindow::setAnchorPoint(sf::Vector2f anchorPt) {
    anchorPoint = anchorPt;
}

void HackerWindow::setAnchorPoint(float anchorPointX, float anchorPointY) {
    anchorPoint = sf::Vector2f(anchorPointX, anchorPointY);
}

sf::Vector2f HackerWindow::getWidthHeight() {
    sf::FloatRect bounds = hackerScreen.getGlobalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

void HackerWindow::setWidthHeight(sf::Vector2f wH) {
    widthHeight = wH;
}

void HackerWindow::setWidthHeight(float width, float height) {
    widthHeight = sf::Vector2f(width, height);
}

sf::Font HackerWindow::getFont() {
    return hackerFont;
}

void HackerWindow::setFont(sf::Font& font){
    hackerFont = font;
}

sf::Color HackerWindow::getTextColor() {
    return textColor;
}

void HackerWindow::setTextColor(const sf::Color& color) {
    textColor = color;
}

void HackerWindow::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    Globals::game->renderWindow.setView(Globals::computerView);

    // sf::RectangleShape debugRect(sf::Vector2f(2000, 2000));
    // debugRect.setPosition(0, 0);
    // debugRect.setFillColor(sf::Color::Green);
    // renderTarget.draw(debugRect);
    
    renderTarget.draw(hackerScreen, states);
    renderTarget.draw(hackerText, states);
    Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
}

void HackerWindow::updateHackerText() {
    std::string newText = "";
    for (std::string line : displayedCode) {
        newText += line + "\n";
    }
    hackerText.setString(newText);
}

void HackerWindow::updateList(char c) {
    if (c == '\n') {
        displayedCode.push_back("");
    } else {
        displayedCode.back() += c;
    }
    if(displayedCode.size() > displayedCodeSize) { // Change when we have bounds working
        displayedCode.pop_front();
    }
    
    updateHackerText();
}

void HackerWindow::clear() {
    displayedCode.clear();
    displayedCode.push_back("");
    updateHackerText();
}

void HackerWindow::update(sf::Time deltaTime) {
}

bool HackerWindow::contains(sf::Vector2f pos) {
    return hackerScreen.getGlobalBounds().contains(pos);
}

void HackerWindow::activate() {
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this);
}

void HackerWindow::deactivate() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}