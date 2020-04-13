#include "hackerWindow.h"
#include <iostream>

HackerWindow::HackerWindow(sf::Vector2f anchorPt, sf::Vector2f wH, sf::Font& font, const sf::Color& color)
    : hackerText(), 
      hackerScreen() {

        anchorPoint = anchorPt;
        widthHeight = wH;
        hackerFont = font;
        textColor = color;
        hackerText.setFont(hackerFont);
        hackerText.setString("Testing One Too Three");
        hackerScreen.setPosition(anchorPoint);
        hackerScreen.setSize(widthHeight);
        hackerScreen.setFillColor(sf::Color::Green);
        hackerText.setPosition(anchorPoint);
    };

HackerWindow::HackerWindow(float anchorPointX, float anchorPointY, float width, float height, sf::Font& font, const sf::Color& color)
    : hackerText(), 
      hackerScreen() {

        anchorPoint = sf::Vector2f(anchorPointX, anchorPointY);
        widthHeight = sf::Vector2f(width, height);
        hackerFont = font;
        textColor = color;
        hackerText.setFont(hackerFont);
        hackerText.setString("Testing One Too Three");
        hackerScreen.setPosition(anchorPoint);
        hackerScreen.setSize(widthHeight);
        hackerScreen.setFillColor(sf::Color::Green);
        hackerText.setPosition(anchorPoint);
    };

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
    return widthHeight;
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
    renderTarget.draw(hackerScreen, states);
    renderTarget.draw(hackerText, states);
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