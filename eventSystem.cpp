#include "eventSystem.hpp"
#include <algorithm>
#include <stdlib.h>

/***************
 * EventHandler
 ***************/

EventSystem::EventHandler* EventSystem::EventHandler::instance = 0;

void EventSystem::EventHandler::processEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
            mouseMoveEvent(event.mouseMove);
            break;
        case sf::Event::MouseButtonReleased:
            mouseDownEvent(event.mouseButton);
            break;
        case sf::Event::MouseButtonReleased:
            mouseUpEvent(event.mouseButton);
            break;
    }
}

bool EventSystem::EventHandler::registerMouseMoveObserver(EventSystem::MouseMoveObserver observer) {
    if (std::find(mouseMoveRegistrants.begin(), mouseMoveRegistrants.end(), observer) == mouseMoveRegistrants.end()) {
        return false;
    } else {
        mouseMoveRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerMouseDownObserver(EventSystem::MouseUpObserver observer) {
    if (std::find(mouseUpRegistrants.begin(), mouseUpRegistrants.end(), observer) == mouseUpRegistrants.end()) {
        return false;
    } else {
        mouseUpRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::registerMouseDownObserver(EventSystem::MouseDownObserver observer) {
    if (std::find(mouseDownRegistrants.begin(), mouseDownRegistrants.end(), observer) == mouseDownRegistrants.end()) {
        return false;
    } else {
        mouseDownRegistrants.push_back(observer);
        return true;
    }
}

bool EventSystem::EventHandler::unregisterMouseMoveObserver(EventSystem::MouseMoveObserver observer) {
    if (std::find(mouseMoveRegistrants.begin(), mouseMoveRegistrants.end(), observer) == mouseMoveRegistrants.end()) {
        mouseMoveRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterMouseDownObserver(EventSystem::MouseUpObserver observer) {
    if (std::find(mouseUpRegistrants.begin(), mouseUpRegistrants.end(), observer) == mouseUpRegistrants.end()) {
        mouseUpRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

bool EventSystem::EventHandler::unregisterMouseDownObserver(EventSystem::MouseDownObserver observer) {
    if (std::find(mouseDownRegistrants.begin(), mouseDownRegistrants.end(), observer) == mouseDownRegistrants.end()) {
        mouseDownRegistrants.remove(observer);
        return true;
    } else {
        return false;
    }
}

void EventSystem::EventHandler::mouseMoveEvent(sf::Event::MouseMoveEvent event) {
    for (MouseMoveObserver observer : mouseMoveRegistrants) {
        observer.mouseMove(event);
    }
}

void EventSystem::EventHandler::mouseDownEvent(sf::Event::MouseButtonEvent event) {
    for (MouseDownObserver observer : mouseDownRegistrants) {
        observer.mouseDown(event);
    }
}

void EventSystem::EventHandler::mouseUpEvent(sf::Event::MouseUpEvent event) {
    for (MouseUpObserver observer : mouseUpRegistrants) {
        observer.mouseUp(event);
    }
}

void* operator EventSystem::EventHandler::new(size_t size) {
    if (instance == 0) {
        return malloc(size);
    } else {
        return instance;
    }
}
