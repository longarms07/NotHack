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
    class TextEnteredObserver;
    class KeyPressedObserver;
    class KeyReleasedObserver;

    // Should be singleton
    class EventHandler : public Singleton<EventHandler> {
        friend EventHandler* Singleton<EventHandler>::getInstance();

        private:
            // Collection should maybe be a map/skiplist
            std::list<MouseMoveObserver*> mouseMoveRegistrants;
            std::list<MouseDownObserver*> mouseDownRegistrants;
            std::list<MouseUpObserver*> mouseUpRegistrants;
            std::list<TextEnteredObserver*> textEnteredRegistrants;
            std::list<KeyPressedObserver*> keyPressedRegistrants;
            std::list<KeyReleasedObserver*> keyReleasedRegistrants;

        public:
            void processEvent(sf::Event);

            bool registerMouseMoveObserver(MouseMoveObserver*);
            bool registerMouseDownObserver(MouseDownObserver*);
            bool registerMouseUpObserver(MouseUpObserver*);
            bool registerTextEnteredObserver(TextEnteredObserver*);
            bool registerKeyPressedObserver(KeyPressedObserver*);
            bool registerKeyReleasedObserver(KeyReleasedObserver*);

            bool unregisterMouseMoveObserver(MouseMoveObserver*);
            bool unregisterMouseDownObserver(MouseDownObserver*);
            bool unregisterMouseUpObserver(MouseUpObserver*);
            bool unregisterTextEnteredObserver(TextEnteredObserver*);
            bool unregisterKeyPressedObserver(KeyPressedObserver*);
            bool unregisterKeyReleasedObserver(KeyReleasedObserver*);

        private:
            EventHandler(); // Should never be called
            void* operator new(size_t); // Should never be called

            void mouseMoveEvent(sf::Event::MouseMoveEvent);
            void mouseDownEvent(sf::Event::MouseButtonEvent);
            void mouseUpEvent(sf::Event::MouseButtonEvent);
            void textEnteredEvent(sf::Event::TextEvent);
            void keyPressedEvent(sf::Event::KeyEvent);
            void keyReleasedEvent(sf::Event::KeyEvent);
    };

    /*Mouse Observers*/

    class MouseMoveObserver {
        public:
            MouseMoveObserver(bool autoRegister=true);
            ~MouseMoveObserver();

            virtual void mouseMove(sf::Event::MouseMoveEvent) = 0;
    };

    class MouseDownObserver {
        public:
            MouseDownObserver(bool autoRegister=true);
            ~MouseDownObserver();

            virtual void mouseDown(sf::Event::MouseButtonEvent) = 0;
    };

    class MouseUpObserver {
        public:
            MouseUpObserver(bool autoRegister=true);
            ~MouseUpObserver();

            virtual void mouseUp(sf::Event::MouseButtonEvent) = 0;
    };

    /*Text Observers*/
    class TextEnteredObserver {
        public:
            TextEnteredObserver(bool autoRegister=true);
            ~TextEnteredObserver();

            virtual void textEntered(sf::Event::TextEvent event) = 0;
    };

    /*Key Observers*/
    class KeyPressedObserver {
        public:
            KeyPressedObserver(bool autoRegister=true);
            ~KeyPressedObserver();

            virtual void keyPressed(sf::Event::KeyEvent) = 0;
    };

    class KeyReleasedObserver {
        public:
            KeyReleasedObserver(bool autoRegister=true);
            ~KeyReleasedObserver();

            virtual void keyReleased(sf::Event::KeyEvent) = 0;
    };
}