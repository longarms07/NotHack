#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list> 

class HackerWindow : public sf::Drawable {
    public:
        HackerWindow(sf::Vector2f anchorPt, sf::Vector2f wH, sf::Font& font, const sf::Color& color);
        HackerWindow(float anchorPointX, float anchorPointY, float width, float height, sf::Font& font, const sf::Color& color);
        sf::Vector2f getAnchorPoint();
        sf::Vector2f getWidthHeight();
        sf::Font getFont();
        sf::Color getTextColor();
        void setAnchorPoint(sf::Vector2f anchorPt);
        void setAnchorPoint(float anchorPointX, float anchorPointY);
        void setWidthHeight(sf::Vector2f wH);
        void setWidthHeight(float width, float height);
        void setFont(sf::Font& font);
        void setTextColor(const sf::Color& color);
        void updateHackerText();
        void setHackerTextFile(std::string filePath);
        void loadNextChar();


    private:
        sf::Font hackerFont; // Font of the text
        sf::Text hackerText; // Textbox that the text is stored within. 
        sf::RectangleShape hackerScreen; // The background screen of the window
        sf::Vector2f anchorPoint; // Top-left pixel of the hacker window
        sf::Vector2f widthHeight; // Width and height of the window
        sf::Color textColor; // Color of the text
        std::list<std::string> displayedCode = { "" };
        const int displayedCodeSize = 5;
        std::ifstream hackerTextFile;

        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
        void updateList(char c);
};

HackerWindow::HackerWindow(sf::Vector2f anchorPt, sf::Vector2f wH, sf::Font& font, const sf::Color& color)
    : hackerText(), 
      hackerScreen() {
        anchorPoint = anchorPt;
        widthHeight = wH;
        hackerFont = font;
        textColor = color;
        hackerText.setFont(hackerFont);
        hackerText.setString("Testing One Too Three");
        hackerScreen.setPosition(anchorPoint);
        hackerScreen.setSize(widthHeight);
        hackerScreen.setFillColor(sf::Color::Green);
        hackerText.setPosition(anchorPoint);
    };

HackerWindow::HackerWindow(float anchorPointX, float anchorPointY, float width, float height, sf::Font& font, const sf::Color& color)
    : hackerText(), 
      hackerScreen() {
        anchorPoint = sf::Vector2f(anchorPointX, anchorPointY);
        widthHeight = sf::Vector2f(width, height);
        hackerFont = font;
        textColor = color;
        hackerText.setFont(hackerFont);
        hackerText.setString("Testing One Too Three");
        hackerScreen.setPosition(anchorPoint);
        hackerScreen.setSize(widthHeight);
        hackerScreen.setFillColor(sf::Color::Green);
        hackerText.setPosition(anchorPoint);
    };

sf::Vector2f HackerWindow::getAnchorPoint() {
    return anchorPoint;
}

void HackerWindow::setAnchorPoint(sf::Vector2f anchorPt) {
    anchorPoint = anchorPt;
}

void HackerWindow::setAnchorPoint(float anchorPointX, float anchorPointY) {
    anchorPoint = sf::Vector2f(anchorPointX, anchorPointY);
}

sf::Vector2f HackerWindow::getWidthHeight() {
    return widthHeight;
}

void HackerWindow::setWidthHeight(sf::Vector2f wH) {
    widthHeight = wH;
}

void HackerWindow::setWidthHeight(float width, float height) {
    widthHeight = sf::Vector2f(width, height);
}

sf::Font HackerWindow::getFont() {
    return hackerFont;
}

void HackerWindow::setFont(sf::Font& font){
    hackerFont = font;
}

sf::Color HackerWindow::getTextColor() {
    return textColor;
}

void HackerWindow::setTextColor(const sf::Color& color) {
    textColor = color;
}

void HackerWindow::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    renderTarget.draw(hackerScreen, states);
    renderTarget.draw(hackerText, states);
}

void HackerWindow::updateHackerText() {
    std::string newText = "";
    for (std::string line : displayedCode) {
        newText += line + "\n";
    }
    hackerText.setString(newText);
}

void HackerWindow::setHackerTextFile(std::string filePath) {
    if (hackerTextFile.is_open()) {
        hackerTextFile.close();
    }

    hackerTextFile.open(filePath);

    if (hackerTextFile.bad()) {
        std::cerr << "Failed to read file, exiting...\n";
        exit (8);
    }
}

void HackerWindow::loadNextChar() {
    if (!hackerTextFile.is_open()) {
        std::cerr << "Tried to read from unopen stream...\n";
        exit (7); // TODO: set exit code
    }

    if (hackerTextFile.bad()) {
        std::cerr << "Error reading from file...\n";
        exit (8);
    }

    if (hackerTextFile.eof()) {
        hackerTextFile.clear();
        hackerTextFile.seekg(0, std::ios::beg);
        updateList('\n');
    } else {
        char nextChar;
        hackerTextFile >> std::noskipws >> nextChar;
        // std::cout << nextChar << '\n';
        updateList(nextChar);
    }
}

void HackerWindow::updateList(char c) {
    if (c == '\n') {
        displayedCode.push_back("");
    } else {
        displayedCode.back() += c;
    }
    if(displayedCode.size() > displayedCodeSize) { // Change when we have bounds working
        displayedCode.pop_front();
    }
    
    updateHackerText();
}