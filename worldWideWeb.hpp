#pragma once
#include <SFML/Graphics.hpp>
#include "eventSystem.hpp"
#include "textField.hpp"
#include "singleton.hpp"
#include "jobSystem.hpp"
#include <list>

/*
TODO:
    - Maybe all the event passing should instead be done by const reference instead
        of by copy?

    - Abstract dragable

    - Check difference between mouse0, 1, 2 and events
    - Implement states better

    - Should Drawable inheritance be virtual?

    - Better way to compare strings?
*/

namespace WorldWideWeb {
    class WindowPart;
    class URLBar;
    class JobButton;

    class BrowserWindow : public sf::Drawable, public EventSystem::MouseMoveObserver, public EventSystem::MouseDownObserver, public EventSystem::MouseUpObserver, public EventSystem::KeyPressedObserver {
        public:
            URLBar* urlBar;
            WindowPart* currentSite;

        private:
            sf::RectangleShape windowBackground;

            sf::Vector2f websiteOffset;

            /*Dragging State*/
            bool dragging;
            sf::Vector2f mouseOffsetFromOrigin;

        public:
            BrowserWindow(sf::Vector2f, sf::Vector2f, sf::Font&);
            ~BrowserWindow();

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

            /*sf::Transformable... but not really (because I don't want to stub everything)*/
            void setPosition(float, float);

            /*EventSystem Observeres*/
            void mouseMove(sf::Event::MouseMoveEvent);
            void mouseDown(sf::Event::MouseButtonEvent);
            void mouseUp(sf::Event::MouseButtonEvent);
            void keyPressed(sf::Event::KeyEvent);

        private:
            void setWebsite(WindowPart*);
            void setWebsitePosition();
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

            /*sf::Transformable... but not really (because I don't want to stub everything)*/
            virtual void setPosition(float, float) = 0;
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
                void setPosition(float, float);
        };

        class Blue : public WindowPart, public Singleton<Blue> {
            friend Blue* Singleton<Blue>::getInstance();

            private:
                sf::RectangleShape background;

            private:
                Blue();
                void* operator new(size_t);

                void draw(sf::RenderTarget&, sf::RenderStates) const;
                void setPosition(float, float);
        };

        /*
        class IRC : public WindowPart {

        }
        */

        class Hackdeed : public WindowPart, public Singleton<Hackdeed> {
            friend Hackdeed* Singleton<Hackdeed>::getInstance();

            private:
                sf::RectangleShape background;
                std::list<JobButton*> jobButtons;

            private:
                Hackdeed();
                void* operator new(size_t);

                void draw(sf::RenderTarget&, sf::RenderStates) const;
                void setPosition(float, float);
        };
    }

    class URLBar : public WindowPart {
        public:
            TextField textField;

        public:
            URLBar(sf::Font&);

            void draw(sf::RenderTarget&, sf::RenderStates) const;
            void setPosition(float, float);
    };

    class JobButton : public WindowPart, public EventSystem::MouseDownObserver {
        private:
            sf::Vector2f widthHeight;

            JobSystem::JobInstance* job;

            sf::RectangleShape background;
            sf::Text jobTitle;
            sf::Text jobPay;

        public:
            JobButton(sf::Vector2f, JobSystem::JobInstance*);

            sf::Vector2f getDimensions();

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

            /*EventSystem Observers*/
            void mouseDown(sf::Event::MouseButtonEvent);

            /*WindowPart*/
            void setPosition(float, float);
    };
}