#pragma once // Tells compiler to include the source file only once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "hackerWindow.h"
#include "cooler.h"
#include "idraggable.h"
#include "coolant.h"
#include "fireWall.h"
#include "worldWideWeb.hpp"
#include "textField.hpp"

class Game {
    public:
        Game();
        ~Game();      
        void run();
        void setDraggable(IDraggable* iDraggable);

    
    private:
        sf::RenderWindow renderWindow;
        sf::Text debugFPS;
        HackerWindow* l33tHackerWindow;
        Cooler* cooler;
        IDraggable* draggable; // The current iDraggable assigned to the mouse. Can only drag one thing at a time.
        WorldWideWeb::BrowserWindow* browserWindow;
        
        void update(sf::Time deltaTime);

        void processEvents();
        
        void render();

        void updateFPSDisplay(sf::Time t);
};

