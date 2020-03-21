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
    }
}

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

/**************
 * Observers
 **************/

EventSystem::MouseMoveObserver::MouseMoveObserver() {
    EventSystem::EventHandler::getInstance()->registerMouseMoveObserver(this);
}

EventSystem::MouseMoveObserver::~MouseMoveObserver() {
    EventSystem::EventHandler::getInstance()->unregisterMouseMoveObserver(this);
}

EventSystem::MouseDownObserver::MouseDownObserver() {
    EventSystem::EventHandler::getInstance()->registerMouseDownObserver(this);
}

EventSystem::MouseDownObserver::~MouseDownObserver() {
    EventSystem::EventHandler::getInstance()->unregisterMouseDownObserver(this);
}

EventSystem::MouseUpObserver::MouseUpObserver() {
    EventSystem::EventHandler::getInstance()->registerMouseUpObserver(this);
}

EventSystem::MouseUpObserver::~MouseUpObserver() {
    EventSystem::EventHandler::getInstance()->unregisterMouseUpObserver(this);
}