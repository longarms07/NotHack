#pragma once
#include <SFML/Graphics.hpp>

namespace WorldWideWeb {
    class WindowPart;

    class BrowserWindow : public sf::Drawable {
        public:
            WindowPart* currentSite;

        private:
            sf::RectangleShape windowBackground;

        public:
            BrowserWindow(sf::Vector2f, sf::Vector2f);
            ~BrowserWindow();

            void draw(sf::RenderTarget&, sf::RenderStates) const;
    };

    /*
    class Internet {
        // Keeps track of sites; the "topography" of the net
    }
    */


    /***************
     * WINDOW PARTS
     ***************/

    class WindowPart : public sf::Drawable {
        // Part of the window, inherited by everything
        // Handles its own rendering and events
        public:
            virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
            virtual void mouseDown();
            virtual void mouseUp();
    };

    namespace Sites {
        // Sites should all follow the singleton pattern, since they have state

        class Bank : public WindowPart {
            public:
                void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
        };

        /*
        class IRC : public WindowPart {

        }

        class Hackdeed : public WindowPart {

        }
        */
    }

    /*
    class URLBar : public WindowPart {

    }
    */
}