#pragma once
#include "textCrawl.hpp"
#include "globals.hpp"
#include "game.h"

/**************************
 * Parameters:
 *  - sf::pText: Full text to display
 *  - bool pClearScreen: If true, the previous text will be cleared before loading this node's text
 *  - bool pSameLine: If false, add a newline before displaying this text
 ***************************/
TextNode::TextNode(sf::String pText, float pDelay, bool pClearScreen=false, bool pSameLine=false) {
    text = pText;
    delay = pDelay;
    clearScreen = pClearScreen;
    sameLine = pSameLine;
}

/****************
 * TextCrawl
 ****************/

/***********************
 * Instantiate the TextCrawl for the given
 * screen dimensions and instantiate its
 * pre-programmed text crawl
 ***********************/
TextCrawl::TextCrawl(float screenWidth, float screenHeight)
    : crawlTextbox(),
      skipTextbox(),
      textNodesList()
{
    // Generate crawl text
    textNodesList.push_back(TextNode("The timeline diverged from ours when the Bangalore Boss;", 1.f));
    textNodesList.push_back(TextNode("the greatest hacker who ever lived, does live, and will live;", 1.f));
    textNodesList.push_back(TextNode("traveled back to the past and invented hacking for the Allies", 1.f));
    textNodesList.push_back(TextNode("ending WWII without further bloodshed\nand making atomic weaponry obsolete before it was even invented", 3.f));

    textNodesList.push_back(TextNode("In the decades that followed,", 1.f, true));
    textNodesList.push_back(TextNode("There was no Cold War; the USSR and US became bros and formed the USS", 1.f));
    textNodesList.push_back(TextNode("The 80s never ended", 1.f));
    textNodesList.push_back(TextNode("The 90s also never ended", 1.f));
    textNodesList.push_back(TextNode("...and hacker culture took over both the Earth and the Moon", 3.f));

    textNodesList.push_back(TextNode("The year is 1990+30 (we had to prevent Y2K somehow)", 1.f, true));
    textNodesList.push_back(TextNode("It is Not the 80s", 1.f));
    textNodesList.push_back(TextNode("It is Not the 90s", 1.f));
    textNodesList.push_back(TextNode("It is the Not80s90s", 2.f));
    textNodesList.push_back(TextNode("\nYou are just an ordinary person...", 1.f));
    textNodesList.push_back(TextNode("...a hacker", 3.f));

    textNodesList.push_back(TextNode("If this wasn't a demo, you would go on to do great, wicked-sick things", 1.f, true));
    textNodesList.push_back(TextNode("This is the demo for...", 3.f));

    textNodesList.push_back(TextNode("NotHack: Weaponized Polymorphic Methods (WPM)", 0.f, true));


    // Set the crawlTextbox information
    crawlTextbox.setFont(Globals::defaultFont);
    crawlTextbox.setCharacterSize(screenWidth/35);

    crawlTextbox.setFillColor(sf::Color::White);
    crawlTextbox.setPosition(screenWidth/30, screenHeight/5);

    // Set skipTextbox information
    skipTextbox.setFont(Globals::defaultFont);
    skipTextbox.setCharacterSize(screenWidth/40);

    skipTextbox.setFillColor(sf::Color::White);
    skipTextbox.setPosition(screenWidth/10, screenHeight-screenHeight/5);

    skipTextbox.setString("Press Space to skip");

    // Set first node
    nextCharIndex = 0;
    currentNode = 0;
    
    targetText = textNodesList[currentNode].text;
    crawlTextbox.setString("_");

    timeUntilNextChar = charDelay;
    timeUntilNextNode = textNodesList[currentNode].delay;
}

/************************
 * Given the deltaTime, display
 * the next character, if applicable, or
 * load the next node, if applicable.
 ************************/
void TextCrawl::update(sf::Time deltaTime) {
    // Crawl display
    timeUntilNextChar -= deltaTime.asSeconds();

    if (timeUntilNextChar <= 0) {
        if (nextCharIndex > targetText.getSize()) {
            timeUntilNextNode -= deltaTime.asSeconds();
            if (timeUntilNextNode <= 0) {
                if (!next()) {
                    skipTextbox.setString("Press Space to Start!");
                }
            }
        } else {
            crawlTextbox.setString(targetText.substring(0, nextCharIndex)+"_");
            timeUntilNextChar = charDelay;
            nextCharIndex++;
        }
    }

    // Skip blinker
    skipBlinkTimer -= deltaTime.asSeconds();
    if (skipBlinkTimer < -skipBlinkDelay/2) {
        skipBlinkTimer = skipBlinkDelay;
    }
}

void TextCrawl::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(crawlTextbox, states);

    if (skipBlinkTimer > 0) {
        target.draw(skipTextbox, states);
    }
}


/********************
 * Load the next node, if any.
 *
 * Returns: If a new node was loaded
 ********************/
bool TextCrawl::next() {
    if (currentNode+1 < textNodesList.size()) {
        TextNode nextNode = textNodesList[++currentNode];

        if (nextNode.clearScreen) {
            targetText = nextNode.text;
            nextCharIndex = 0;
        } else if (nextNode.sameLine) {
            targetText += nextNode.text;
        } else {
            targetText += "\n"+nextNode.text;
        }

        timeUntilNextChar = charDelay;
        timeUntilNextNode = nextNode.delay;

        return true;
    } else {
        return false;
    }
}