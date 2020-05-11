#pragma once
#include <SFML/Graphics.hpp>
#include "singleton.hpp"

/*****************************************************
 * EventSystem:
 *      - namespace for all subjects and observers
 *        relating to event (input) handling
 * ***************************************************/

namespace EventSystem {
    class MouseMoveObserver;
    class MouseDownObserver;
    class MouseUpObserver;
    class TextEnteredObserver;
    class KeyPressedObserver;
    class KeyReleasedObserver;

    /********************************
     * Subject responsible for handling
     * events and passing them to the
     * appropriate observers
     ********************************/
    class EventHandler : public Singleton<EventHandler> {
        friend EventHandler* Singleton<EventHandler>::getInstance();

        private:
            /************************************
             * Each list corresponds to a group
             * of observers for a specific event
             **************************************/
            std::list<MouseMoveObserver*> mouseMoveRegistrants;
            std::list<MouseDownObserver*> mouseDownRegistrants;
            std::list<MouseUpObserver*> mouseUpRegistrants;
            std::list<TextEnteredObserver*> textEnteredRegistrants;
            std::list<KeyPressedObserver*> keyPressedRegistrants;
            std::list<KeyReleasedObserver*> keyReleasedRegistrants;

            std::list<MouseMoveObserver*> mouseMoveRegistrantsToRemove;
            std::list<MouseDownObserver*> mouseDownRegistrantsToRemove;
            std::list<MouseUpObserver*> mouseUpRegistrantsToRemove;
            std::list<TextEnteredObserver*> textEnteredRegistrantsToRemove;
            std::list<KeyPressedObserver*> keyPressedRegistrantsToRemove;
            std::list<KeyReleasedObserver*> keyReleasedRegistrantsToRemove;

        public:
            void processEvent(sf::Event); // Process event and call the event handling functions for the relevant observers
            void removeClearedObservers(); // Function called at the very end of event handling; some objects are told to
                                           // unsubscribe after an event, but still need to finish event processing before that)

            // Functions for registering and unregistering observers
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

            // Processing for specific events
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
            virtual ~MouseMoveObserver();

            virtual void mouseMove(sf::Event::MouseMoveEvent) = 0;
    };

    class MouseDownObserver {
        public:
            MouseDownObserver(bool autoRegister=true);
            virtual ~MouseDownObserver();

            virtual void mouseDown(sf::Event::MouseButtonEvent) = 0;
    };

    class MouseUpObserver {
        public:
            MouseUpObserver(bool autoRegister=true);
            virtual ~MouseUpObserver();

            virtual void mouseUp(sf::Event::MouseButtonEvent) = 0;
    };

    /*Text Observers*/
    class TextEnteredObserver {
        public:
            TextEnteredObserver(bool autoRegister=true);
            virtual ~TextEnteredObserver();

            virtual void textEntered(sf::Event::TextEvent event) = 0;
    };

    /*Key Observers*/
    class KeyPressedObserver {
        public:
            KeyPressedObserver(bool autoRegister=true);
            virtual ~KeyPressedObserver();

            virtual void keyPressed(sf::Event::KeyEvent) = 0;
    };

    class KeyReleasedObserver {
        public:
            KeyReleasedObserver(bool autoRegister=true);
            virtual ~KeyReleasedObserver();

            virtual void keyReleased(sf::Event::KeyEvent) = 0;
    };
}