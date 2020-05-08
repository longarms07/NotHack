#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>

enum OutroState {
    accessFullGame,
    hackerWindowBlueScreen,
    fullBlueScreen,
    done
};

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
        sf::Time maxTime;
        bool timeActive = false;
        std::list<std::string> textQueue; 
        OutroState state = accessFullGame;

        void displayAccessFullGame();
        void displayHackerWindowBlueScreen();
        void displayFullBlueScreen();
        void displayFinalText();
        void startTimer();
        
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
        
};