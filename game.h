#pragma once // Tells compiler to include the source file only once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "hackerWindow.h"
#include "cooler.h"
#include "idraggable.h"
#include "coolant.h"
#include "globals.hpp"
#include "worldWideWeb.hpp"
#include "textField.hpp"
#include "complication.hpp"
#include "jobSystem.hpp"
#include "registerable.hpp"

class Game {
    public:
        Game();
        ~Game();      
        void run();
        void setDraggable(IDraggable*);
        void activateWindow(Registerable*);

        sf::RenderWindow renderWindow;
    
    private:
        sf::Text debugFPS;
        Cooler* cooler;
        IDraggable* draggable; // The current iDraggable assigned to the mouse. Can only drag one thing at a time.
        Registerable* currentWindow;
        //WorldWideWeb::BrowserWindow* browserWindow;
        
        void update(sf::Time);

        void processEvents();
        
        void render();

        void updateFPSDisplay(sf::Time);
};

