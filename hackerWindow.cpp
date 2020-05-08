#include "hackerWindow.h"
#include <iostream>

/******************************************************************************
 * HackerWindow Constructor -- Constructor for creating a new instance.       *
 * Parameters:                                                                *
 *      -anchorP: A Vector2 of Floats representing the anchor point at which  *
 *       the hackerWindow is drawn.                                           *
 *      -wH: A Vector2 of Floats with the x value being the width of the      *
 *        HackerWindow and the y value being the height.                      *
 *      -font: A reference to the text font for the window.                   *
 *      -color: A reference to the background color for the hackerWindow.     *
 ******************************************************************************/
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
}

/******************************************************************************
 * OVERLOAD                                                                   *
 * HackerWindow Constructor -- Constructor for creating a new instance.       *
 * Parameters:                                                                *
 *      -anchorPointX: A float representing the x value of the anchor point.  *
 *      -anchorPointY: A float representing the y value of the anchor point.  *
 *      -width: A float representing the width of the HackerWindow.           *
 *      -height: A float representing the height of the HackerWindow.         *
 *      -font: A reference to the text font for the window.                   *
 *      -color: A reference to the background color for the hackerWindow.     *
 ******************************************************************************/
HackerWindow::HackerWindow(float anchorPointX, float anchorPointY, float width, float height, sf::Font& font, const sf::Color& color)
    : HackerWindow(sf::Vector2f(anchorPointX, anchorPointY), sf::Vector2f(width, height), font, color)
{ }

/******************************************************************************
 * getAnchorPoint -- Getter method for the Hackerwindow's AnchorPoint         *
 * Returns:                                                                   *
 *      -A Vector2 Float of the HackerWindow's anchorpoint.                   *
 ******************************************************************************/
sf::Vector2f HackerWindow::getAnchorPoint() {
    return anchorPoint;
}

/******************************************************************************
 * setAnchorPoint -- Setter method for the Hackerwindow's AnchorPoint         *
 * Parameters:                                                                *
 *      -anchorPt: A Vector2 Float of the HackerWindow's anchorpoint.         *
 ******************************************************************************/
void HackerWindow::setAnchorPoint(sf::Vector2f anchorPt) {
    anchorPoint = anchorPt;
}

/******************************************************************************
 * OVERLOAD                                                                   *
 * setAnchorPoint -- Setter method for the Hackerwindow's AnchorPoint         *
 * Parameters:                                                                *
 *      -anchorPointX: A float representing the x value of the anchor point.  *
 *      -anchorPointY: A float representing the y value of the anchor point.  *
 ******************************************************************************/
void HackerWindow::setAnchorPoint(float anchorPointX, float anchorPointY) {
    anchorPoint = sf::Vector2f(anchorPointX, anchorPointY);
}

/******************************************************************************
 * getWidthHeight -- Getter method for the Hackerwindow's Width and Height.   *
 * Returns:                                                                   *
 *      -A Vector2 Float of the HackerWindow's width and height.              *
 ******************************************************************************/
sf::Vector2f HackerWindow::getWidthHeight() {
    sf::FloatRect bounds = hackerScreen.getGlobalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

/******************************************************************************
 * setWidthHeight -- Setter method for the Hackerwindow's Width and Height.   *
 * Parameters:                                                                *
 *      -WidthHeight: A Vector2 Float of the HackerWindow's width and height. *
 ******************************************************************************/
void HackerWindow::setWidthHeight(sf::Vector2f wH) {
    widthHeight = wH;
}

/******************************************************************************
 * setWidthHeight -- Setter method for the Hackerwindow's Width and Height.   *
 * Parameters:                                                                *
 *      -width: A float representing the width of the HackerWindow.           *
 *      -height: A float representing the height of the HackerWindow.         *
 ******************************************************************************/
void HackerWindow::setWidthHeight(float width, float height) {
    widthHeight = sf::Vector2f(width, height);
}

/******************************************************************************
 * getFont -- Getter method for the Hackerwindow's text font.                 *
 * Returns:                                                                   *
 *      -The font of the HackerWindow's text.                                 *
 ******************************************************************************/
sf::Font HackerWindow::getFont() {
    return hackerFont;
}

/******************************************************************************
 * setFont -- Getter method for the Hackerwindow's text font.                 *
 * Parameters:                                                                *
 *      -font: The font of the HackerWindow's text.                           *
 ******************************************************************************/
void HackerWindow::setFont(sf::Font& font){
    hackerFont = font;
}


/******************************************************************************
 * getTextColor -- Getter method for the Hackerwindow's text color.           *
 * Returns:                                                                   *
 *      -The color for the HackerWindow's text.                               *
 ******************************************************************************/
sf::Color HackerWindow::getTextColor() {
    return textColor;
}

/******************************************************************************
 * setTextColor -- Getter method for the Hackerwindow's text color.           *
 * Parameters:                                                                *
 *      -color: The color for the HackerWindow's text.                        *
 ******************************************************************************/
void HackerWindow::setTextColor(const sf::Color& color) {
    textColor = color;
}

/******************************************************************************
 * draw -- Renders the Cooler graphics.                                       *
 * Overrides the Virtual function from Drawable.                              *
 ******************************************************************************/
void HackerWindow::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    Globals::game->renderWindow.setView(Globals::computerView);
    renderTarget.draw(hackerScreen, states);
    renderTarget.draw(hackerText, states);
    Globals::game->renderWindow.setView(Globals::game->renderWindow.getDefaultView());
}

/******************************************************************************
 * updateHackerText -- Adds each line of displayedCode to the hackerText.     *
 ******************************************************************************/
void HackerWindow::updateHackerText() {
    std::string newText = "";
    for (std::string line : displayedCode) {
        newText += line + "\n";
    }
    hackerText.setString(newText);
}

/******************************************************************************
 * updateList -- Updates the displayedCodeList by 1 more character, and       *
 *      Removes the oldest line of the list if it has gotten too long.        *
 * Parameters:                                                                *
 *      -c: The char to add to the displayedCode list.                        *
 ******************************************************************************/
void HackerWindow::updateList(char c) {
    if (c == '\n') {
        displayedCode.push_back("");
    } else {
        displayedCode.back() += c;
    }
    if(displayedCode.size() > displayedCodeSize) { // If we have too many lines of code remove the oldest
        displayedCode.pop_front();
    }
    
    updateHackerText();
}

/******************************************************************************
 * clear -- Removes all lines of displayedCode, clearing the list.            *
 ******************************************************************************/
void HackerWindow::clear() {
    displayedCode.clear();
    displayedCode.push_back("");
    updateHackerText();
}

/******************************************************************************
 * update -- Called every frame.                                              *
 * Parameters:                                                                *
 *      -deltaTime: the time since the last frame.                            *
 ******************************************************************************/
void HackerWindow::update(sf::Time deltaTime) {
}


/******************************************************************************
 * contains -- Checks whether or not the input position is within the bounds  *
 *      of the hackerWindow.                                                  *
 * Parameters:                                                                *
 *      -pos: A Vector2 Float containing a position to check.                 *
 * Returns:                                                                   *
 *      -True if pos is within the hackerScreen's bounds.                     *
 *      -False if pos is not within the hackerScreen's bounds.                *
 ******************************************************************************/
bool HackerWindow::contains(sf::Vector2f pos) {
    return hackerScreen.getGlobalBounds().contains(pos);
}

/******************************************************************************
 * activate -- Subscribes the HackerWindow to the Render System.              *
 * Overrides the Virtual function from Registerable.                          *
 ******************************************************************************/
void HackerWindow::activate() {
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this);
}

/******************************************************************************
 * deactivate -- Unsubscribes the HackerWindow to the Render System.          *
 * Overrides the Virtual function from Registerable.                          *
 ******************************************************************************/
void HackerWindow::deactivate() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
}


