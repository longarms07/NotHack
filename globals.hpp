#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include "worldWideWeb.hpp"

/*******************************************
 * The global namespace is for
 * all objects and constants that
 * are accessed by many different classes.
 * This allows for simplified imports and
 * access.
 *******************************************/
namespace Globals {
    // References
    sf::Font defaultFont; // Default font used for most text
    sf::Texture computerSpriteSheet; // Spritesheet for the entire hacking scene, excluding the cooler
    sf::Music backgroundMusic; // The object responsible for playing music

    sf::String openingMusicPath = "TimeQ.ogg";
    sf::String hackingMusicPath = "RetroracingMenu.ogg";
    sf::String finalJobMusicPath = "RetroracingRivalRacer.ogg";

    sf::View computerView; // The sf::View used to crop what the computer monitor displayers

    // Pointers
    Game* game;
    HackerWindow* hackerWindow;
    WorldWideWeb::BrowserWindow* browserWindow;
}