#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"
#include "worldWideWeb.hpp"

namespace Globals {
    sf::Font defaultFont;
    Game* game;
    HackerWindow* hackerWindow;
    WorldWideWeb::BrowserWindow* browserWindow;
}