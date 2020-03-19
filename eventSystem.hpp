#pragma once
#include <SFML/Graphics.hpp>

namespace EventSystem {
    // Should be singleton
    class EventHandler {
        public:
            static EventHandler* instance;

        private:
            // Collection should maybe be a map/skiplist
            std::list<MouseMoveObserver> mouseMoveRegistrants;
            std::list<MouseDownObserver> mouseDownRegistrants;
            std::list<MouseUpObserver> mouseUpRegistrants;

        public:
            void processEvent(sf::Event);

            bool registerMouseMoveObserver(MouseMoveObserver);
            bool registerMouseDownObserver(MouseDownObserver);
            bool registerMouseUpObserver(MouseUpObserver);

            bool unregisterMouseMoveObserver(MouseMoveObserver);
            bool unregisterMouseDownObserver(MouseDownObserver);
            bool unregisterMouseUpObserver(MouseUpObserver);

        private:
            EventHandler(); // Should never be called

            void mouseMoveEvent(sf::Event::MouseMoveEvent);
            void mouseDownEvent(sf::Event::MouseButtonEvent);
            void mouseUpEvent(sf::Event::MouseButtonEvent);
    };

    class MouseMoveObserver() {
        public:
            virtual mouseMove(sf::Event::MouseMoveEvent) = 0;
    };

    class MouseDownObserver() {
        public:
            virtual mouseDown(sf::Event::MouseButtonEvent) = 0;
    };

    class MouseUpObserver() {
        public:
            virtual mouseUp(sf::Event::MouseButtonEvent) = 0;
    };
}