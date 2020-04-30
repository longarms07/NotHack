#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"
#include "worldWideWeb.hpp"

namespace Globals {
    // References
    sf::Font defaultFont;
    sf::Texture computerSpriteSheet;

    sf::View computerView; // Define what the view shows in the global world

    // Pointers
    Game* game;
    HackerWindow* hackerWindow;
    WorldWideWeb::BrowserWindow* browserWindow;

}