#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "hackerWindow.h"
#include "cooler.h"
#include "idraggable.h"
#include "coolant.h"

class Game {
    public:
        Game();
        ~Game();      
        void run();
        void setDraggable(IDraggable* iDraggable);
        HackerWindow* getHackerWindow();
    
    private:
        sf::RenderWindow renderWindow;
        sf::CircleShape testCircle;
        sf::Text debugFPS;
        HackerWindow* l33tHackerWindow;
        sf::Font font;
        Cooler* cooler;
        IDraggable* draggable;
        
        void update(sf::Time deltaTime);

        void processEvents();
        
        void render();

        void updateFPSDisplay(sf::Time t);
};

