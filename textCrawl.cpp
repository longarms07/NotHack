#pragma once
#include "textCrawl.hpp"
#include "globals.hpp"
#include "game.h"

TextNode::TextNode(sf::String pText, float pDelay, bool pClearScreen=false, bool pSameLine=false) {
    text = pText;
    delay = pDelay;
    clearScreen = pClearScreen;
    sameLine = pSameLine;
}

TextCrawl::TextCrawl(float screenWidth, float screenHeight)
    : crawlTextbox(),
      textNodesList()
{
    // Generate crawl text
    textNodesList.push_back(TextNode("The timeline diverged from ours when the Bangalore Boss;", 5.f));
    textNodesList.push_back(TextNode("the greatest hacker who ever lived, does live, and will live;", 5.f));
    textNodesList.push_back(TextNode("traveled back to the past and invented hacking for the Allies", 5.f));
    textNodesList.push_back(TextNode("ending WWII without further bloodshed\nand making atomic weaponry obsolete before it was even invented", 12.f));

    textNodesList.push_back(TextNode("In the decades that followed,", 4.f, true));
    textNodesList.push_back(TextNode("There was no Cold War; the USSR and US became bros and formed the USS", 7.f));
    textNodesList.push_back(TextNode("The 80s never ended", 3.f));
    textNodesList.push_back(TextNode("The 90s also never ended", 3.f));
    textNodesList.push_back(TextNode("...and hacker culture took over both the Earth and the Moon", 8.f));

    textNodesList.push_back(TextNode("The year is 1990+30 (we had to prevent Y2K somehow)", 6.f, true));
    textNodesList.push_back(TextNode("It is Not the 80s", 3.f));
    textNodesList.push_back(TextNode("It is Not the 90s", 3.f));
    textNodesList.push_back(TextNode("It is the Not80s90s", 5.f));
    textNodesList.push_back(TextNode("\nYou are just an ordinary person...", 4.f));
    textNodesList.push_back(TextNode("...a hacker", 6.f));

    textNodesList.push_back(TextNode("If this wasn't a demo, you would go on to do great, wicked-sick things", 5.f, true));
    textNodesList.push_back(TextNode("This is the demo for...", 5.f));

    textNodesList.push_back(TextNode("NotHack: Weaponized Polymorphic Methods (WPM)", 5.f, true));


    // Set the crawlTextbox information
    crawlTextbox.setFont(Globals::defaultFont);
    crawlTextbox.setCharacterSize(screenWidth/35);

    crawlTextbox.setFillColor(sf::Color::White);
    crawlTextbox.setPosition(screenWidth/30, screenHeight/5);

    // Set first node
    currentNode = 0;
    crawlTextbox.setString(textNodesList[currentNode].text);
    timeUntilNextNode = textNodesList[currentNode].delay;
}

void TextCrawl::update(sf::Time deltaTime) {
    timeUntilNextNode -= deltaTime.asSeconds();

    if (timeUntilNextNode <= 0) {
        if (!next()) {
            Globals::game->currentState = Game::state::GAME;
        }
    }
}

void TextCrawl::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(crawlTextbox, states);
}

bool TextCrawl::next() {
    if (currentNode+1 < textNodesList.size()) {
        TextNode nextNode = textNodesList[++currentNode];

        if (nextNode.clearScreen) {
            crawlTextbox.setString(nextNode.text);
        } else if (nextNode.sameLine) {
            crawlTextbox.setString(crawlTextbox.getString()+nextNode.text);
        } else {
            crawlTextbox.setString(crawlTextbox.getString()+"\n"+nextNode.text);
        }

        timeUntilNextNode = nextNode.delay;

        return true;
    } else {
        return false;
    }
}