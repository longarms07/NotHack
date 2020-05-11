#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**************************************************
 * TextNode:
 *  - Information on the current text to display
 **************************************************/
class TextNode {
    public:
        sf::String text;
        float delay; // How long to wait before displaying next text
        bool clearScreen; // Should the previous text be cleared?
        bool sameLine; // Should this text be on the same line as the previous?

    public:
        TextNode(sf::String, float, bool, bool);
};

class TextCrawl : public sf::Drawable {
    private:
        int currentNode; // Current TextNode being displayed
        std::vector<TextNode> textNodesList;

        float timeUntilNextChar; // Time until the next character of the currentNode should be displayed
        float timeUntilNextNode; // How long until the next TextNode should be loaded
        float skipBlinkTimer; // Timer for the skip text's blinking

        int nextCharIndex; // Index of the next char to display
        sf::String targetText; // Full text, once all characters have been displayed; the substring targetText(0, nextCharIndex) is displayed

        sf::Text crawlTextbox; // Textbox for the text crawl
        sf::Text skipTextbox; // Textbox for the skip button

        const float charDelay = 0.035f; // Delay before displaying the next character
        const float skipBlinkDelay = 2.5f; // Delay before blinking the skip text off

    public:
        TextCrawl(float, float);

        void update(sf::Time deltaTime);

        void draw(sf::RenderTarget&, sf::RenderStates) const;

    private:
        bool next(); // Load next TextNode
};