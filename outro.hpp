#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>

/******************************************************************************
 * OutroState:                                                                *
 *      -Enums representing the 4 screen states of the outro. Used for        *
 *        changing states.                                                    *
 ******************************************************************************/
enum OutroState {
    accessFullGame,
    hackerWindowBlueScreen,
    fullBlueScreen,
    done // Thank you for playing screen
};


/******************************************************************************
 * Outro:                                                                     *
 *      -The Outro of the game. Consists of 4 screens: A fake "victory"       *
 *       screen to access the game from on the HackerWindow, a blue screen of *
 *       death on the HackerWindow, a blue screen of death on the game window,*
 *       and a ending "Thank you for playing!" Screen on the game window.     *
 *      -Derived class of Drawable.                                           *
 ******************************************************************************/
class Outro : public sf::Drawable{
    public:
        Outro();
        ~Outro();

        void update(sf::Time deltaTime);
        void next(); 

    private:
        sf::Text outroText; 
        sf::RectangleShape outroSprite;
        sf::Font font;
        sf::Time timer = sf::Time::Zero; 
        sf::Time maxTime; // How long to wait to do the next action
        bool timeActive = false;
        std::list<std::string> textQueue; // The text to add to outro text
        OutroState state = accessFullGame;

        void displayAccessFullGame(); // Transitions to the first state, the fake victory screen
        void displayHackerWindowBlueScreen(); // Transitions to the second state, HackerWindow Blue Screen of death
        void displayFullBlueScreen(); // Transitions to the third state, Game Window Blue Screen of death
        void displayFinalText(); // Transitions to the fourth state, the "Thank you for playing."
        void startTimer(); // Resets the timer.
        
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
        
};