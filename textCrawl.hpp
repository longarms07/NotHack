#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TextNode {
    public:
        sf::String text;
        float delay;
        bool clearScreen;
        bool sameLine;

    public:
        TextNode(sf::String, float, bool, bool);
};

class TextCrawl : public sf::Drawable {
    private:
        int currentNode;
        std::vector<TextNode> textNodesList;

        float timeUntilNextNode;

        sf::Text crawlTextbox;

    public:
        TextCrawl(float, float);

        void update(sf::Time deltaTime);

        void draw(sf::RenderTarget&, sf::RenderStates) const;

    private:
        bool next();
};