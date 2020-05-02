#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include "worldWideWeb.hpp"

namespace Globals {
    // References
    sf::Font defaultFont;
    sf::Texture computerSpriteSheet;
    sf::Music backgroundMusic;

    sf::String openingMusicPath = "TimeQ.ogg";
    sf::String hackingMusicPath = "RetroracingMenu.ogg";
    sf::String finalJobMusicPath = "RetroracingRivalRacer.ogg";

    sf::View computerView; // Define what the view shows in the global world

    // Pointers
    Game* game;
    HackerWindow* hackerWindow;
    WorldWideWeb::BrowserWindow* browserWindow;

}