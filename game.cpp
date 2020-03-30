#include "game.h"
#include "globals.hpp"
#include "hackerWindow.cpp" // Must import cpp files here in order to get the implementations for each class
#include "cooler.cpp"
#include "coolant.cpp"
#include "fireWall.cpp"
#include "progressBar.cpp"
#include "worldWideWeb.cpp"
#include "eventSystem.cpp"
#include "singleton.cpp"
#include "textField.cpp"
#include "jobSystem.cpp"
#include "renderSystem.cpp"

Game::Game()
    : renderWindow(sf::VideoMode(640,480), "NotHack: WPM"),
      debugFPS()
{
    debugFPS.setFont(Globals::defaultFont);
    
    cooler = new Cooler(400.f, 0.f);
    browserWindow = new WorldWideWeb::BrowserWindow(sf::Vector2f(300.f,50.f), sf::Vector2f(300.f,300.f), Globals::defaultFont);

    RenderSystem::RenderHandler::getInstance()->registerDrawable(browserWindow);
    RenderSystem::RenderHandler::getInstance()->registerDrawable(cooler);

    std::cout << "The font has been set. Ready to hacktivate.\n";
    debugFPS.setString("FPS Text Initialized");
    debugFPS.setFillColor(sf::Color::Blue);
    debugFPS.setPosition(sf::Vector2f(0.f,0.f));
};

Game::~Game() {
    delete cooler;
    delete browserWindow;
    if (draggable != NULL) delete draggable;
}

void Game::run() {
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    Globals::hackerWindow->updateHackerText();
    JobSystem::JobHandler::getInstance()->loadJob(JobSystem::Factories::genericJob());

    while (renderWindow.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        if (timeSinceLastUpdate > timePerFrame) {
            updateFPSDisplay(timeSinceLastUpdate);
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timeSinceLastUpdate);
        }

        render();
    }
}

void Game::setDraggable(IDraggable* iDraggable) {
    // If there is a current draggable call onDragEnd on it.
    if (draggable != NULL) draggable->onDragEnd(draggable->getPosition()); 
    draggable = iDraggable;
}

void Game::update(sf::Time deltaTime) {
    Globals::hackerWindow->update(deltaTime);
    cooler->update(deltaTime);
}

void Game::processEvents() {
    sf::Event event;
    while (renderWindow.pollEvent(event))
    {

        switch (event.type) {
            case sf::Event::KeyReleased:
                std::cout << "Key " << event.key.code << " has been released!!!!!\n";
                break;
            case sf::Event::Closed:
                renderWindow.close();
                break;
            case sf::Event::MouseMoved:
                if (draggable != NULL) draggable->onDragMove(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                /*if (cooler->getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    if (!cooler->isMouseOver()) {
                        cooler->onMouseOver(true);
                        std::cout << "The Mouse is over the cooler!\n";
                    }
                }
                else if (cooler->isMouseOver()) {
                    cooler->onMouseOver(false);
                    std::cout << "The Mouse has left the cooler!\n";
                }*/
                break;
            case sf::Event::MouseButtonReleased:
                // If there is currently a draggable, when the mouse is clicked call it's onDragEnd.
                // Since onDragEnd will either destroy it or make the draggable not our concern, set the pointer to null.
                if (draggable != NULL) {
                    draggable->onDragEnd(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    draggable = NULL;
                    // RenderSystem::RenderHandler::getInstance()->unregisterDrawable(&draggable->getSprite());
                }
                /*if (cooler->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    cooler->onClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    std::cout << "Clicked on Cooler!\n";
                }*/
                break;
        }   
        
        EventSystem::EventHandler::getInstance()->processEvent(event);
    }
}

void Game::render() {
    renderWindow.clear();
    renderWindow.draw(debugFPS);
    renderWindow.draw(*RenderSystem::RenderHandler::getInstance());

    //renderWindow.draw(*browserWindow);

    //renderWindow.draw(*cooler);
    //renderWindow.draw(*Globals::hackerWindow);

    // if (draggable!=NULL) renderWindow.draw(draggable->getSprite());

    renderWindow.display();
}

void Game::updateFPSDisplay(sf::Time t) {
    float denominator = t.asSeconds();
    float fps = -1.f;
    if(denominator != 0.f)
        fps = 1 / denominator;
    debugFPS.setString("FPS = "+std::to_string(fps));
}


int main() {
    if(!Globals::defaultFont.loadFromFile("Oxanium-Regular.ttf")){
        std::cout << "The font could not be loaded! Oh noes!!!\n";
        exit(2);
    }else{
        std::cout << "The file loaded! Oh Frabtuous Day!!!\n";
    }

    Globals::hackerWindow = new HackerWindow(50.f,50.f,200.f,300.f, Globals::defaultFont, sf::Color::White);
    RenderSystem::RenderHandler::getInstance()->registerDrawable(Globals::hackerWindow);

    Globals::game.run();
}