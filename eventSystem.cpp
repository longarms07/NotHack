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


/*Un/Registration*/

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

bool EventSystem::EventHandler::unregisterMouseMoveObserver(MouseMoveObserver* observer) {
    if (std::find(mouseMoveRegistrants.begin(), mouseMoveRegistrants.end(), observer) != mouseMoveRegistrants.end()) {
        mouseMoveRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterMouseDownObserver(MouseDownObserver* observer) {
    if (std::find(mouseDownRegistrants.begin(), mouseDownRegistrants.end(), observer) != mouseDownRegistrants.end()) {
        mouseDownRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterMouseUpObserver(MouseUpObserver* observer) {
    if (std::find(mouseUpRegistrants.begin(), mouseUpRegistrants.end(), observer) != mouseUpRegistrants.end()) {
        mouseUpRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterTextEnteredObserver(TextEnteredObserver* observer) {
    if (std::find(textEnteredRegistrants.begin(), textEnteredRegistrants.end(), observer) != textEnteredRegistrants.end()) {
        textEnteredRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterKeyPressedObserver(KeyPressedObserver* observer) {
    if (std::find(keyPressedRegistrants.begin(), keyPressedRegistrants.end(), observer) != keyPressedRegistrants.end()) {
        keyPressedRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterKeyReleasedObserver(KeyReleasedObserver* observer) {
    if (std::find(keyReleasedRegistrants.begin(), keyReleasedRegistrants.end(), observer) != keyReleasedRegistrants.end()) {
        keyReleasedRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

/*Event Handling*/

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
    for (KeyPressedObserver* observer : keyPressedRegistrants) {
        observer->keyPressed(event);
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