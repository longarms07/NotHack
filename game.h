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
#include "textCrawl.hpp"

class Game {
    public:
        enum state {INTRO, GAME, OUTRO}currentState;

    private:
        sf::Text debugFPS;
        sf::Sprite* computerSprite;
        sf::Sprite* backgroundSprite;
        Cooler* cooler;
        IDraggable* draggable; // The current iDraggable assigned to the mouse. Can only drag one thing at a time.
        Registerable* currentWindow;
        //WorldWideWeb::BrowserWindow* browserWindow;

        TextCrawl textCrawl;

    public:
        Game();
        ~Game();      
        void run();
        void setDraggable(IDraggable*);
        void activateWindow(Registerable*);

        sf::RenderWindow renderWindow;
    
    private:
        void update(sf::Time);

        void processEvents();
        
        void render();

        void updateFPSDisplay(sf::Time);
};

