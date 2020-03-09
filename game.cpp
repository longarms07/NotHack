#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "hackerWindow.cpp"


class Game {
    public:
        Game()
        : renderWindow(sf::VideoMode(640,480), "NotHack: WPM"),
        debugFPS(),
        testCircle()
        {
            if(!font.loadFromFile("Oxanium-Regular.ttf")){
                std::cout << "The font could not be loaded! Oh noes!!!\n";
                exit(2);
            }else{
                std::cout << "The file loaded! Oh Frabtuous Day!!!\n";
            }
            debugFPS.setFont(font);
            
            l33tHackerWindow = new HackerWindow(50.f,50.f,200.f,300.f, font, sf::Color::White);
            std::cout << "The font has been set. Ready to hacktivate.\n";
            debugFPS.setString("FPS Text Initialized");
            debugFPS.setFillColor(sf::Color::Blue);
            debugFPS.setPosition(sf::Vector2f(0.f,0.f));
            testCircle.setRadius(200.f);
            testCircle.setPosition(0.f,0.f);
            testCircle.setFillColor(sf::Color::Red);
        };

        ~Game() {
            delete l33tHackerWindow;
        }
        
        void run() {
            const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;

            l33tHackerWindow->updateHackerText();
            l33tHackerWindow->setHackerTextFile("hello-world.txt");

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
    
    private:
        sf::RenderWindow renderWindow;
        sf::CircleShape testCircle;
        sf::Text debugFPS;
        HackerWindow* l33tHackerWindow;
        sf::Font font;
        
        void update(sf::Time deltaTime) {
        }

        void processEvents() {
            sf::Event event;
            while (renderWindow.pollEvent(event))
            {
                switch (event.type) {
                    case sf::Event::KeyReleased:
                        std::cout << "Key " << event.key.code << " has been released!!!!!\n";
                        l33tHackerWindow->loadNextChar();
                        break;
                    case sf::Event::Closed:
                        renderWindow.close();
                        break;
                }   
            }
        }
        
        void render() {
            renderWindow.clear();
            //renderWindow.draw(testCircle);
            renderWindow.draw(debugFPS);
            renderWindow.draw(*l33tHackerWindow);
            renderWindow.display();
        }

        void updateFPSDisplay(sf::Time t) {
            float denominator = t.asSeconds();
            float fps = -1.f;
            if(denominator != 0.f)
                fps = 1 / denominator;
            debugFPS.setString("FPS = "+std::to_string(fps));
        }
};








int main() {
    Game game;
    game.run();
}