#pragma once
#include "progressBar.h"
#include "globals.hpp"

/******************************************************************************
 * Progress Bar Constructor -- Constructor for creating a new instance of a   *
 *      ProgressBar (without text).                                           *
 * Parameters:                                                                *
 *      -anchorPoint: A Vector2 of Floats representing the anchor point at    *
 *        which the progress bar is drawn.                                    *
 *      -widthHeight: A Vector2 of Floats with the x value being the width of *
 *        the progress bar and the y value being the height.                  *
 *      -color: The color to make the middle (progress) rectangle.            *
 *      -maxProgress: The maximum possible value for tracked progress (100%). *
 ******************************************************************************/
ProgressBar::ProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress)
    : bottomLayer(), progressLayer(), text()
{
    sf::Vector2f barPosition = sf::Vector2f(anchorPoint.x, anchorPoint.y);
    constructProgressBar(barPosition, widthHeight, color, maxProgress);
}

/******************************************************************************
 * OVERLOAD                                                                   *
 * Progress Bar Constructor -- Constructor for creating a new instance of a   *
 *      ProgressBar (with text).                                              *
 * Parameters:                                                                *
 *      -anchorPoint: A Vector2 of Floats representing the anchor point at    *
 *        which the progress bar is drawn.                                    *
 *      -widthHeight: A Vector2 of Floats with the x value being the width of *
 *        the progress bar and the y value being the height.                  *
 *      -color: The color to make the middle (progress) rectangle.            *
 *      -maxProgress: The maximum possible value for tracked progress (100%). *
 *      -displayText: A string of text to display on the progress bar.        *
 *      -fontSize: An integer representing the size to display the text at.   *
 ******************************************************************************/
ProgressBar::ProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress, std::string displayText, int fontSize)
    : ProgressBar(anchorPoint, widthHeight, color, maxProgress)
{
    text.setFont(Globals::defaultFont);
    text.setCharacterSize(fontSize);
    text.setString(displayText);
    text.setPosition(progressLayer.getPosition());
}

/******************************************************************************
 * getProgress -- Getter method for the amount of progress made so far.       *
 * Returns:                                                                   *
 *      -A float holding the progress made so far.                            *
 ******************************************************************************/
float ProgressBar::getProgress() {
    return progress;
}

/******************************************************************************
 * setProgress -- Setter method for the amount of progress made so far.       *
 * Parameters:                                                                *
 *      -p: A float holding the progress made so far.                         *
 ******************************************************************************/
void ProgressBar::setProgress(float p) {
    progress = p;
    // Update the visual display of progress with the new amount
    setProgressDimensions();
}

/******************************************************************************
 * incrementProgress -- Increases the amount of progress made so far.         *
 * Parameters:                                                                *
 *      -toAdd: A float holding the amount of progress to add the progress    *
 *        made so far.                                                        *
 ******************************************************************************/
void ProgressBar::incrementProgress(float toAdd) {
    //std::cout << "Progress Before: " << progress << " , to Add: " << toAdd << " , max: " << max; // Debug
    progress += toAdd;
    if (progress > max) progress = max;
    //std::cout << " , Progress after: " << progress << "\n"; // Debug
    setProgressDimensions();
}

/******************************************************************************
 * decrementProgress -- Increases the amount of progress made so far.         *
 * Parameters:                                                                *
 *      -toRemove: A float holding the amount of progress to subtract from    *
 *        the progress made so far.                                           *
 ******************************************************************************/
void ProgressBar::decrementProgress(float toRemove) {
    progress -= toRemove;
    if (progress < 0) progress = 0;
    setProgressDimensions();
}

/******************************************************************************
 * constructProgressBar -- Creates the Grey part of the progress bar and      *
 *      calculates the maximum bounds.                                        *    
 * Parameters:                                                                *
 *      -anchorPoint: A Vector2 of Floats representing the anchor point at    *
 *        which the progress bar is drawn.                                    *
 *      -widthHeight: A Vector2 of Floats with the x value being the width of *
 *        the progress bar and the y value being the height.                  *
 *      -color: The color to make the middle (progress) rectangle.            *
 *      -maxProgress: The maximum possible value for tracked progress (100%). *
 ******************************************************************************/
void ProgressBar::constructProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress) {
    std::cout << "Contsructed progress bar" << std::endl;
    bottomLayer.setPosition(anchorPoint);
    bottomLayer.setSize(widthHeight);
    bottomLayer.setFillColor(sf::Color(112,128,144)); // Grey
    progressLayer.setPosition(sf::Vector2f(anchorPoint.x+(widthHeight.x * 0.05f), anchorPoint.y+(widthHeight.y * 0.1f))); // Offset by 10% of dimensions 
    maxProgressDimensions = sf::Vector2f(widthHeight.x * 0.9f, widthHeight.y * 0.8f);
    progressLayer.setFillColor(color);
    max = maxProgress;
    progress = 0;
    setProgressDimensions();
}

/******************************************************************************
 * setProgressDimensions -- Sets the length of the middle rectangle relative  *
 *      to the percentage of progress made.                                   *    
 * Parameters:                                                                *
 *      -anchorPoint: A Vector2 of Floats representing the anchor point at    *
 *        which the progress bar is drawn.                                    *
 *      -widthHeight: A Vector2 of Floats with the x value being the width of *
 *        the progress bar and the y value being the height.                  *
 *      -color: The color to make the middle (progress) rectangle.            *
 *      -maxProgress: The maximum possible value for tracked progress (100%). *
 ******************************************************************************/
void ProgressBar::setProgressDimensions() { 
    if (progress == 0) progressLayer.setSize(sf::Vector2f(0, maxProgressDimensions.y));
    else { 
        float progressPercent = progress / max;
        progressLayer.setSize(sf::Vector2f(maxProgressDimensions.x * progressPercent, maxProgressDimensions.y));
    }
}

/******************************************************************************
 * draw -- Renders the Progress Bar graphics.                                 *
 * Overrides the Virtual function from Drawable.                              *
 ******************************************************************************/
void ProgressBar::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    renderTarget.draw(bottomLayer, states);
    renderTarget.draw(progressLayer, states);
    renderTarget.draw(text, states);
}