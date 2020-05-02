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

        float timeUntilNextChar;
        float timeUntilNextNode;
        float skipBlinkTimer;

        int nextCharIndex;
        sf::String targetText;

        sf::Text crawlTextbox;
        sf::Text skipTextbox;

        const float charDelay = 0.035f;
        const float skipBlinkDelay = 2.5f;

    public:
        TextCrawl(float, float);

        void update(sf::Time deltaTime);

        void draw(sf::RenderTarget&, sf::RenderStates) const;

    private:
        bool next();
};