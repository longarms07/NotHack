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
#include "outro.hpp"
#include "hackerText.hpp"

/*****************************************************
 * Game:
 *      - The main SFML class that draws the window,
 *        does the initial event processing, initializes
 *        objects, and start the recursive drawing of
 *        objects that inherit sf::Drawable
 * Visual:
 *     - The game Window and all objects within it
 ****************************************************/
class Game {
    public:
        enum state {INTRO, GAME, OUTRO}currentState; // If the state is displaying the intro, playing the normal game, or playing the outro
        sf::RenderWindow renderWindow; // The application window

    private:
        sf::Text debugFPS; // The framerate counter
        sf::Sprite* computerSprite; // Sprite for the computer
        sf::Sprite* backgroundSprite; // Sprite for the room (behind the computer) and desk
        Cooler* cooler; // Cooler object (see Cooler and Cooland documentation)
        IDraggable* draggable; // The current iDraggable assigned to the mouse. Can only drag one thing at a time.
        Registerable* currentWindow; // The current window being displayed (HackerWindow or WWW browser)

        TextCrawl textCrawl; // Object responsible for displaying the intro text (see TextCrawl documentation)
        Outro* outro; // Object responsible for playing the outro (see Outro documentation)

    public:
        Game();
        ~Game();

        void run(); // Function that initializes objects and then calls update, processEvents, and render when applicable
        void setDraggable(IDraggable*); // Set the object the mouse is dragging
        void activateWindow(Registerable*); // Display a new window and hide the old one
        void startOutro();
    
    private:
        void update(sf::Time); // Called every frame, calls the processEvents and render functions when applicable

        void processEvents(); // Processes input events such as mouse and keyboard
        
        void render(); // Renders objects that extend sf::Drawable

        void updateFPSDisplay(sf::Time); // Updates the time displayed on debugFPS
};

