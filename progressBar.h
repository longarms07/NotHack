#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


/******************************************************************************
 * ProgressBar:                                                               *
 *      -A GUI element that displays the progress towards a certain goal.     *
 *      -A derived class of Drawable                                          *
 * Visual:                                                                    *
 *      -A Grey Rectangle with a colored rectangle inside of it that grows as *
 *        the amount of progress made increased.                              *
 *      -Optional: A message displayed over the progress bar.                 *
 ******************************************************************************/
class ProgressBar : public sf::Drawable {
    private:
        sf::Text text; // The text that is displayed over the progress bar, optional
        sf::RectangleShape bottomLayer; // The botton of the progress bar, set dimensions
        sf::RectangleShape progressLayer; // The layer representing the progress made so far. 
        float progress; // The amount of progress thus far
        float max; // The maximum amount of progress allowed
        sf::Vector2f maxProgressDimensions; // The maximum dimensions of the progress layer

    public:
        ProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress);
        // Optional constructor to display text over the progress bar
        ProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress, std::string displayText, int fontSize);
        float getProgress();
        void setProgress(float p); // Sets the total progress based on the maximum possible progress. progress < max, > 0
        void incrementProgress(float toAdd); // Adds to the progress so far, goes to at most maximum
        void decrementProgress(float toRemove); // Removes from the progress so far, sets to at least 0


    private:
        void constructProgressBar(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Color color, float maxProgress); // Called by constructors for common code
        void setProgressDimensions(); // Updates the dimensions of the progress bar
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
};