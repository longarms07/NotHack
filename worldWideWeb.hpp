#pragma once
#include <SFML/Graphics.hpp>
#include "eventSystem.hpp"
#include "textField.hpp"
#include "singleton.hpp"
#include "jobSystem.hpp"
#include "registerable.hpp"
#include <list>

/*****************************
 * Namespace for all classes
 * related to the WorldWideWeb
 * and browser
 *****************************/
namespace WorldWideWeb {
    class WindowPart;
    class URLBar;
    class JobButton;

    /************************************
     * BrowserWindow:
     *  - Class responsible for all event
     *    handling and rendering relating
     *    to the WWW and browser
     * Visual:
     *  - The browser windows inside the
    *     computer monitor
     ************************************/
    class BrowserWindow : public sf::Drawable,
                          public EventSystem::MouseMoveObserver,
                          public EventSystem::MouseDownObserver,
                          public EventSystem::MouseUpObserver,
                          public EventSystem::KeyPressedObserver,
                          public Registerable
    {
        public:
            URLBar* urlBar; // TextField for website URLs
            WindowPart* currentSite; // Current site being shown

        private:
            sf::Sprite hackscapeSprite; // Sprite for the browser background

            sf::Vector2f monitorOffset;
            sf::Vector2f urlOffset;
            sf::Vector2f websiteOffset;

            /*Dragging State*/
            // Deprecated, used to dragging windows around
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

            /*Registerable*/
            // Show/hide the browser
            void activate();
            void deactivate();

        private:
            void setWebsite(WindowPart*);
            void setWebsitePosition();
    };


    /***************
     * WINDOW PARTS
     ***************/

    /*********************
     * An abstrct class for
     * all objects that make up a website
     * or browser window;
     * includes event handling
     * and rendering
     *********************/
    class WindowPart : public sf::Drawable, public Registerable {
        public:
            virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

            /*sf::Transformable... but not really (because I don't want to stub everything)*/
            virtual void setPosition(float, float) = 0;
    };

    /********************************************
     * Namespace for websites. Website follow
     * the singleton pattern because there is always
     * only one instance of a website at any given time.
     ********************************************/
    namespace Sites {
        /********************
         * Testing website that displays red
         ********************/
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

        /********************
         * Testing website that displays blue
         ********************/
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

        /********************
         * Job board website where
         * player goes to select
         * hacking jobs
         ********************/
        class Hackdeed : public WindowPart, public Singleton<Hackdeed> {
            friend Hackdeed* Singleton<Hackdeed>::getInstance();

            private:
                sf::RectangleShape background; // Background of website

                sf::Vector2f buttonOffset; // Margin between each job button

                std::list<JobButton*> jobButtons; // List of buttons for each job available

            public:
                /*Registerable*/
                void activate(); // Show site
                void deactivate(); // Hide site

            private:
                Hackdeed();
                void* operator new(size_t);

                void draw(sf::RenderTarget&, sf::RenderStates) const;
                void setPosition(float, float);
        };
    }

    /**********************************
     * Class responsible for taking in
     * URLs and using them to switch sites
     **********************************/
    class URLBar : public WindowPart {
        public:
            TextField textField;

        public:
            URLBar(sf::Font&);

            void draw(sf::RenderTarget&, sf::RenderStates) const;
            void setPosition(float, float);

            /*Registerable*/
            void activate();
            void deactivate();
    };

    /******************************
     * JobButton:
     *  - Class that allows player to select
     *    (and activate) a hacking job
     *  - Is the interface between the browser,
     *    job, player, and JobSystem
     * Visual:
     *   - Displays a clickable button
     ******************************/
    class JobButton : public WindowPart, public EventSystem::MouseDownObserver {
        private:
            sf::Vector2f widthHeight; // Dimensions of the button

            JobSystem::JobInstance* job; // Job the button is representing

            sf::RectangleShape background; // Background for hte button
            sf::Text jobTitle;
            sf::Text jobPay; // Text for job reward

        public:
            JobButton(sf::Vector2f, JobSystem::JobInstance*);

            sf::Vector2f getDimensions();

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

            /*EventSystem Observers*/
            void mouseDown(sf::Event::MouseButtonEvent);

            /*WindowPart*/
            void setPosition(float, float);

            /*Registerable*/
            void activate();
            void deactivate();

        private:
            void loadStrings(); // Load the correct text for jobTitle and jobPay, mainly called when the job changes
    };
}