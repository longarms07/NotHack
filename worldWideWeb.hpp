#pragma once
#include <SFML/Graphics.hpp>
#include "eventSystem.hpp"
#include "textField.hpp"
#include "singleton.hpp"

/*
TODO:
    - Maybe all the event passing should instead be done by const reference instead
        of by copy?

    - Abstract dragable

    - Check difference between mouse0, 1, 2 and events
    - Implement states better

    - Implement sf::Transform support
    - Implement generic bounds (instead of using bounding box)

    - Should Drawable inheritance be virtual?

    - Transform hierarchy

    - Better way to compare strings?
*/

namespace WorldWideWeb {
    class WindowPart;
    class URLBar;

    class BrowserWindow : public sf::Drawable, public EventSystem::MouseMoveObserver, public EventSystem::MouseDownObserver, public EventSystem::MouseUpObserver, public EventSystem::KeyPressedObserver {
        public:
            URLBar* urlBar;
            WindowPart* currentSite;

        private:
            sf::RectangleShape windowBackground;

            /*Dragging State*/
            bool dragging;
            sf::Vector2f mouseOffsetFromOrigin;

        public:
            BrowserWindow(sf::Vector2f, sf::Vector2f, sf::Font&);
            ~BrowserWindow();

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

            /*EventSystem Observeres*/
            void mouseMove(sf::Event::MouseMoveEvent);
            void mouseDown(sf::Event::MouseButtonEvent);
            void mouseUp(sf::Event::MouseButtonEvent);
            void keyPressed(sf::Event::KeyEvent);
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
            virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
            // virtual void mouseDown();
            // virtual void mouseUp();
    };

    namespace Sites {
        // Sites should all follow the singleton pattern, since they have state

        // class Bank : public WindowPart {
        //     public:
        //         void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
        // };

        class Red : public WindowPart, public Singleton<Red> {
            friend Red* Singleton<Red>::getInstance();

            private:
                sf::RectangleShape background;

            private:
                Red();
                void* operator new(size_t);

                void draw(sf::RenderTarget&, sf::RenderStates) const;
        };

        class Blue : public WindowPart, public Singleton<Blue> {
            friend Blue* Singleton<Blue>::getInstance();

            private:
                sf::RectangleShape background;

            private:
                Blue();
                void* operator new(size_t);

                void draw(sf::RenderTarget&, sf::RenderStates) const;
        };

        /*
        class IRC : public WindowPart {

        }

        class Hackdeed : public WindowPart {

        }
        */
    }

    class URLBar : public WindowPart {
        public:
            TextField textField;

        public:
            URLBar(sf::Font&);

            void draw(sf::RenderTarget&, sf::RenderStates) const;
    };
}