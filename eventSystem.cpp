#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include "eventSystem.hpp"

/***************
 * EventHandler
 ***************/

EventSystem::EventHandler::EventHandler() { }

void* EventSystem::EventHandler::operator new(size_t size) {
    return malloc(size);
}

/*************
 * The function that game passes events to.
 * Events are then handed off to the relevant processing functions.
 * Parameters:
 *  - sf::Event event: the event to be processed
 *************/
void EventSystem::EventHandler::processEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
            mouseMoveEvent(event.mouseMove);
            break;
        case sf::Event::MouseButtonPressed:
            mouseDownEvent(event.mouseButton);
            break;
        case sf::Event::MouseButtonReleased:
            mouseUpEvent(event.mouseButton);
            break;
        case sf::Event::TextEntered:
            textEnteredEvent(event.text);
            break;
        case sf::Event::KeyPressed:
            keyPressedEvent(event.key);
            break;
        case sf::Event::KeyReleased:
            keyReleasedEvent(event.key);
            break;
    }
}


/******************
 * Each method takes a specific observer
 * and registers it to receive events
 ******************/

bool EventSystem::EventHandler::registerMouseMoveObserver(MouseMoveObserver* observer) {
    if (std::find(mouseMoveRegistrants.begin(), mouseMoveRegistrants.end(), observer) != mouseMoveRegistrants.end()) {
       return false;
    } else {
        mouseMoveRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerMouseDownObserver(MouseDownObserver* observer) {
    if (std::find(mouseDownRegistrants.begin(), mouseDownRegistrants.end(), observer) != mouseDownRegistrants.end()) {
        return false;
    } else {
        mouseDownRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerMouseUpObserver(MouseUpObserver* observer) {
    if (std::find(mouseUpRegistrants.begin(), mouseUpRegistrants.end(), observer) != mouseUpRegistrants.end()) {
       return false;
    } else {
        mouseUpRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerTextEnteredObserver(TextEnteredObserver* observer) {
    if (std::find(textEnteredRegistrants.begin(), textEnteredRegistrants.end(), observer) != textEnteredRegistrants.end()) {
        return false;
    } else {
        textEnteredRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerKeyPressedObserver(KeyPressedObserver* observer) {
    if (std::find(keyPressedRegistrants.begin(), keyPressedRegistrants.end(), observer) != keyPressedRegistrants.end()) {
        return false;
    } else {
        keyPressedRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerKeyReleasedObserver(KeyReleasedObserver* observer) {
    if (std::find(keyReleasedRegistrants.begin(), keyReleasedRegistrants.end(), observer) != keyReleasedRegistrants.end()) {
        return false;
    } else {
        keyReleasedRegistrants.push_back(observer);
        return true;
    }
}


/******************
 * Unregistration works similar to registration,
 * but observers are removed after all events are processed
 * (end of frame) by removeClearedObservers(). This hapens after the unregistration
 * process
 ******************/

bool EventSystem::EventHandler::unregisterMouseMoveObserver(MouseMoveObserver* observer) {
    if (std::find(mouseMoveRegistrants.begin(), mouseMoveRegistrants.end(), observer) != mouseMoveRegistrants.end()) {
        mouseMoveRegistrantsToRemove.push_back(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterMouseDownObserver(MouseDownObserver* observer) {
    if (std::find(mouseDownRegistrants.begin(), mouseDownRegistrants.end(), observer) != mouseDownRegistrants.end()) {
        mouseDownRegistrantsToRemove.push_back(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterMouseUpObserver(MouseUpObserver* observer) {
    if (std::find(mouseUpRegistrants.begin(), mouseUpRegistrants.end(), observer) != mouseUpRegistrants.end()) {
        mouseUpRegistrantsToRemove.push_back(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterTextEnteredObserver(TextEnteredObserver* observer) {
    if (std::find(textEnteredRegistrants.begin(), textEnteredRegistrants.end(), observer) != textEnteredRegistrants.end()) {
        textEnteredRegistrantsToRemove.push_back(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterKeyPressedObserver(KeyPressedObserver* observer) {
    if (std::find(keyPressedRegistrants.begin(), keyPressedRegistrants.end(), observer) != keyPressedRegistrants.end()) {
        keyPressedRegistrantsToRemove.push_back(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterKeyReleasedObserver(KeyReleasedObserver* observer) {
    if (std::find(keyReleasedRegistrants.begin(), keyReleasedRegistrants.end(), observer) != keyReleasedRegistrants.end()) {
        keyReleasedRegistrantsToRemove.push_back(observer);
        return true;
    } else {
        return false;
    }
}


/***************
 * Removes unregistered observers.
 * Occurs after all events are processed (end of frame)
 ***************/

void EventSystem::EventHandler::removeClearedObservers() {
    for (MouseMoveObserver* ob : mouseMoveRegistrantsToRemove) {
        mouseMoveRegistrants.remove(ob);
    }
    mouseMoveRegistrantsToRemove.clear();

    for (MouseDownObserver* ob : mouseDownRegistrantsToRemove) {
        mouseDownRegistrants.remove(ob);
    }
    mouseDownRegistrantsToRemove.clear();

    for (MouseUpObserver* ob : mouseUpRegistrantsToRemove) {
        mouseUpRegistrants.remove(ob);
    }
    mouseUpRegistrantsToRemove.clear();

    for (TextEnteredObserver* ob : textEnteredRegistrantsToRemove) {
        textEnteredRegistrants.remove(ob);
    }
    textEnteredRegistrantsToRemove.clear();

    for (KeyPressedObserver* ob : keyPressedRegistrantsToRemove) {
        keyPressedRegistrants.remove(ob);
    }
    keyPressedRegistrantsToRemove.clear();

    for (KeyReleasedObserver* ob : keyReleasedRegistrantsToRemove) {
        keyReleasedRegistrants.remove(ob);
    }
    keyReleasedRegistrantsToRemove.clear();
}

/*Event Handling*/
/****************
 * Methods that pass event handling to the relevant observers
 ****************/

void EventSystem::EventHandler::mouseMoveEvent(sf::Event::MouseMoveEvent event) {
    for (MouseMoveObserver* observer : mouseMoveRegistrants) {
        observer->mouseMove(event);
    }
}

void EventSystem::EventHandler::mouseDownEvent(sf::Event::MouseButtonEvent event) {
    for (MouseDownObserver* observer : mouseDownRegistrants) {
        observer->mouseDown(event);
    }
}

void EventSystem::EventHandler::mouseUpEvent(sf::Event::MouseButtonEvent event) {
    for (MouseUpObserver* observer : mouseUpRegistrants) {
        observer->mouseUp(event);
    }
}

void EventSystem::EventHandler::textEnteredEvent(sf::Event::TextEvent event) {
    // std::cout << event.unicode << std::endl;
    if (event.unicode > 31 && event.unicode < 127) {
        for (TextEnteredObserver* observer : textEnteredRegistrants) {
            observer->textEntered(event);
        }
    } else {
        // Do nothing for non-latin+punctuation characters
    }
}

void EventSystem::EventHandler::keyPressedEvent(sf::Event::KeyEvent event) {
    if(event.code >= 0) { // don't include -1
        for (KeyPressedObserver* observer : keyPressedRegistrants) {
            observer->keyPressed(event);
        }
    }
}

void EventSystem::EventHandler::keyReleasedEvent(sf::Event::KeyEvent event) {
    for (KeyReleasedObserver* observer : keyReleasedRegistrants) {
        observer->keyReleased(event);
    }
}

/**************
 * Observers
 **************/

/********************
 * All observer constructors take an optional parameter (default is true)
 * autoRegisters that, if true, automatically subscribes the observer to
 * EventHandler.
 ********************/

/*Mouse Observers*/

EventSystem::MouseMoveObserver::MouseMoveObserver(bool autoRegister) {
    if (autoRegister)
        EventSystem::EventHandler::getInstance()->registerMouseMoveObserver(this);
}

EventSystem::MouseMoveObserver::~MouseMoveObserver() {
    EventSystem::EventHandler::getInstance()->unregisterMouseMoveObserver(this);
}

EventSystem::MouseDownObserver::MouseDownObserver(bool autoRegister) {
    if (autoRegister)
        EventSystem::EventHandler::getInstance()->registerMouseDownObserver(this);
}

EventSystem::MouseDownObserver::~MouseDownObserver() {
    EventSystem::EventHandler::getInstance()->unregisterMouseDownObserver(this);
}

EventSystem::MouseUpObserver::MouseUpObserver(bool autoRegister) {
    if (autoRegister)
        EventSystem::EventHandler::getInstance()->registerMouseUpObserver(this);
}

EventSystem::MouseUpObserver::~MouseUpObserver() {
    EventSystem::EventHandler::getInstance()->unregisterMouseUpObserver(this);
}

/*Text Observers*/
EventSystem::TextEnteredObserver::TextEnteredObserver(bool autoRegister) {
    if (autoRegister)
        EventSystem::EventHandler::getInstance()->registerTextEnteredObserver(this);
}

EventSystem::TextEnteredObserver::~TextEnteredObserver() {
    EventSystem::EventHandler::getInstance()->unregisterTextEnteredObserver(this);
}

/*Key Observers*/
EventSystem::KeyPressedObserver::KeyPressedObserver(bool autoRegister) {
    if (autoRegister)
        EventSystem::EventHandler::getInstance()->registerKeyPressedObserver(this);
}

EventSystem::KeyPressedObserver::~KeyPressedObserver() {
    EventSystem::EventHandler::getInstance()->unregisterKeyPressedObserver(this);
}

EventSystem::KeyReleasedObserver::KeyReleasedObserver(bool autoRegister) {
    if (autoRegister)
        EventSystem::EventHandler::getInstance()->registerKeyReleasedObserver(this);
}

EventSystem::KeyReleasedObserver::~KeyReleasedObserver() {
    EventSystem::EventHandler::getInstance()->unregisterKeyReleasedObserver(this);
}