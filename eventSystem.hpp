#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.hpp"

/*
TODO:
    - Maybe all the event passing should instead be done by const reference instead
        of by copy?

    - Should observers automatically register themselves?
    - Should observers automatically unregister themselves when destroyed?
*/

namespace EventSystem {
    class MouseMoveObserver;
    class MouseDownObserver;
    class MouseUpObserver;

    // Should be singleton
    class EventHandler : public Singleton<EventHandler> {
        friend EventHandler* Singleton<EventHandler>::getInstance();

        private:
            // Collection should maybe be a map/skiplist
            std::list<MouseMoveObserver*> mouseMoveRegistrants;
            std::list<MouseDownObserver*> mouseDownRegistrants;
            std::list<MouseUpObserver*> mouseUpRegistrants;

        public:
            void processEvent(sf::Event);

            bool registerMouseMoveObserver(MouseMoveObserver*);
            bool registerMouseDownObserver(MouseDownObserver*);
            bool registerMouseUpObserver(MouseUpObserver*);

            bool unregisterMouseMoveObserver(MouseMoveObserver*);
            bool unregisterMouseDownObserver(MouseDownObserver*);
            bool unregisterMouseUpObserver(MouseUpObserver*);

        private:
            EventHandler(); // Should never be called
            void* operator new(size_t); // Should never be called

            void mouseMoveEvent(sf::Event::MouseMoveEvent);
            void mouseDownEvent(sf::Event::MouseButtonEvent);
            void mouseUpEvent(sf::Event::MouseButtonEvent);
    };

    class MouseMoveObserver {
        public:
            MouseMoveObserver();
            ~MouseMoveObserver();

            virtual void mouseMove(sf::Event::MouseMoveEvent) = 0;
    };

    class MouseDownObserver {
        public:
            MouseDownObserver();
            ~MouseDownObserver();

            virtual void mouseDown(sf::Event::MouseButtonEvent) = 0;
    };

    class MouseUpObserver {
        public:
            MouseUpObserver();
            ~MouseUpObserver();

            virtual void mouseUp(sf::Event::MouseButtonEvent) = 0;
    };
}