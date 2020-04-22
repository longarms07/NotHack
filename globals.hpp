#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"
#include "worldWideWeb.hpp"

namespace Globals {
    sf::Font defaultFont;
    sf::Texture computerSpriteSheet;

    Game* game;
    HackerWindow* hackerWindow;
    WorldWideWeb::BrowserWindow* browserWindow;
}