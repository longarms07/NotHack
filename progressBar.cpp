#pragma once
#include "progressBar.h"
#include "globals.hpp"

ProgressBar::ProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress)
    : bottomLayer(), progressLayer(), text()
{
    sf::Vector2f barPosition = sf::Vector2f(anchorPoint.x, anchorPoint.y-widthHeight.x);
    constructProgressBar(barPosition, widthHeight, color, maxProgress);
}

ProgressBar::ProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress, std::string displayText, int fontSize)
    : ProgressBar(anchorPoint, widthHeight, color, maxProgress)
{
    text.setFont(Globals::defaultFont);
    text.setCharacterSize(fontSize);
    text.setString(displayText);
    text.setPosition(progressLayer.getPosition());
}

float ProgressBar::getProgress() {
    return progress;
}

void ProgressBar::setProgress(float p) {
    progress = p;
    setProgressDimensions();
}

void ProgressBar::incrementProgress(float toAdd) {
    //std::cout << "Progress Before: " << progress << " , to Add: " << toAdd << " , max: " << max;
    progress += toAdd;
    if (progress > max) progress = max;
    //std::cout << " , Progress after: " << progress << "\n";
    setProgressDimensions();
}

void ProgressBar::decrementProgress(float toRemove) {
    progress -= toRemove;
    if (progress < 0) progress = 0;
    setProgressDimensions();
}

void ProgressBar::constructProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress) {
    bottomLayer.setPosition(anchorPoint);
    bottomLayer.setSize(widthHeight);
    bottomLayer.setFillColor(sf::Color(112,128,144)); // Grey
    progressLayer.setPosition(sf::Vector2f(anchorPoint.x+(widthHeight.x * 0.05), anchorPoint.y+(widthHeight.y * 0.1))); // Offset by 10% of dimensions 
    maxProgressDimensions = sf::Vector2f(widthHeight.x * 0.9, widthHeight.y * 0.8);
    progressLayer.setFillColor(color);
    max = maxProgress;
    progress = 0;
    setProgressDimensions();
}

void ProgressBar::setProgressDimensions() { 
    if (progress == 0) progressLayer.setSize(sf::Vector2f(0, maxProgressDimensions.y));
    else { 
        float progressPercent = progress / max;
        progressLayer.setSize(sf::Vector2f(maxProgressDimensions.x * progressPercent, maxProgressDimensions.y));
    }
}

void ProgressBar::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    renderTarget.draw(bottomLayer, states);
    renderTarget.draw(progressLayer, states);
    renderTarget.draw(text, states);
}