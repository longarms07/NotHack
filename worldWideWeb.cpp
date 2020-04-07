#include "worldWideWeb.hpp"
#include "eventSystem.hpp"
#include "globals.hpp"
#include <iostream>
#include <string>

WorldWideWeb::BrowserWindow::BrowserWindow(sf::Vector2f anchorPoint, sf::Vector2f widthHeight, sf::Font& font)
    : windowBackground(),
      websiteOffset(0.f, 100.f)
{

    windowBackground.setPosition(anchorPoint);
    windowBackground.setSize(widthHeight);
    windowBackground.setFillColor(sf::Color(85, 85, 85));

    urlBar = new URLBar(font);
    urlBar->setPosition(anchorPoint.x, anchorPoint.y);
    setWebsite(WorldWideWeb::Sites::Red::getInstance());

    dragging = false;
}

WorldWideWeb::BrowserWindow::~BrowserWindow() {
    delete urlBar;
}

void WorldWideWeb::BrowserWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(windowBackground, states);

    target.draw(*urlBar, states);
    target.draw(*currentSite, states);
}

void WorldWideWeb::BrowserWindow::setPosition(float x, float y) {
    windowBackground.setPosition(x, y);
    urlBar->setPosition(x, y);
    setWebsitePosition();
}

void WorldWideWeb::BrowserWindow::setWebsitePosition() {
    sf::Vector2f newSitePosition = websiteOffset+windowBackground.getPosition();
    currentSite->setPosition(newSitePosition.x, newSitePosition.y);
}

void WorldWideWeb::BrowserWindow::mouseMove(sf::Event::MouseMoveEvent event) {
    if (dragging) {
        sf::Vector2f eventLocation(event.x, event.y);
        sf::Vector2f newPosition = eventLocation - mouseOffsetFromOrigin;
        setPosition(newPosition.x, newPosition.y);
    }
}

void WorldWideWeb::BrowserWindow::mouseDown(sf::Event::MouseButtonEvent event) {
    sf::Vector2f eventLocation(event.x, event.y);

    if (windowBackground.getGlobalBounds().contains(eventLocation)) {
        // std::cout << "Mouse down in bounds" << std::endl;
        mouseOffsetFromOrigin = eventLocation - windowBackground.getPosition();
        dragging = true;
    } else {
        // std::cout << "Mouse down outside bounds" << std::endl;
    }
}

void WorldWideWeb::BrowserWindow::keyPressed(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Return && urlBar->textField.isFocused()) {
        std::string comparableString = static_cast<std::string>(urlBar->textField.getText());
        if (comparableString == "red") {
            // std::cout << "red found!" << std::endl;
            setWebsite(WorldWideWeb::Sites::Red::getInstance());
        } else if (comparableString == "blue") {
            // std::cout << "blue found!" << std::endl;
            setWebsite(WorldWideWeb::Sites::Blue::getInstance());
        } else if (comparableString == "www.hackdeed.com") {
            setWebsite(WorldWideWeb::Sites::Hackdeed::getInstance());
        }
    }
}

void WorldWideWeb::BrowserWindow::mouseUp(sf::Event::MouseButtonEvent event) {
    // std::cout << "Mouse up event" << std::endl;
    dragging = false;
}

void WorldWideWeb::BrowserWindow::setWebsite(WindowPart* newSite) {
    currentSite = newSite;
    setWebsitePosition();
}

WorldWideWeb::URLBar::URLBar(sf::Font& font)
    : textField(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 50.f), font)
{ }

void WorldWideWeb::URLBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(textField, states);
}

void WorldWideWeb::URLBar::setPosition(float x, float y) {
    textField.setPosition(x, y);
}


// Red
WorldWideWeb::Sites::Red::Red()
    : background()
{
    background.setSize(sf::Vector2f(300.f, 200.f));
    background.setFillColor(sf::Color::Red);
}

void* WorldWideWeb::Sites::Red::operator new(size_t size) {
    return malloc(size);
}

void WorldWideWeb::Sites::Red::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
}

void WorldWideWeb::Sites::Red::setPosition(float x, float y) {
    background.setPosition(x, y);
}


// Blue
WorldWideWeb::Sites::Blue::Blue()
    : background()
{
    background.setSize(sf::Vector2f(300.f, 200.f));
    background.setFillColor(sf::Color::Blue);
}

void* WorldWideWeb::Sites::Blue::operator new(size_t size) {
    return malloc(size);
}

void WorldWideWeb::Sites::Blue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
}

void WorldWideWeb::Sites::Blue::setPosition(float x, float y) {
    background.setPosition(x, y);
}


// Hackdeed
WorldWideWeb::Sites::Hackdeed::Hackdeed()
    : background()
{
    background.setSize(sf::Vector2f(300.f, 200.f));
    background.setFillColor(sf::Color::Yellow);

    // Initialize buttons
    jobButtons.push_back(new JobButton(sf::Vector2f(300.f, 100.f), JobSystem::Factories::genericJob()));
    jobButtons.push_back(new JobButton(sf::Vector2f(300.f, 100.f), JobSystem::Factories::fireWallTestJob()));
}

void* WorldWideWeb::Sites::Hackdeed::operator new(size_t size) {
    return malloc(size);
}

void WorldWideWeb::Sites::Hackdeed::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);

    // Draw job buttons
    for (JobButton* jobButton : jobButtons) {
        target.draw(*jobButton, states);
    }
}

void WorldWideWeb::Sites::Hackdeed::setPosition(float x, float y) {
    background.setPosition(x, y);

    // Set button positions
    int i=0;
    for (JobButton* jobButton : jobButtons) {
        jobButton->setPosition(x, y+(1.1*i*jobButton->getDimensions().y));
        i++;
    }
}

// JobButton
WorldWideWeb::JobButton::JobButton(sf::Vector2f pWidthHeight, JobSystem::JobInstance* instance)
    : background(pWidthHeight)
{
    widthHeight = pWidthHeight;

    job = instance;

    jobTitle.setString("Test");
    jobTitle.setFont(Globals::defaultFont);
    jobTitle.setFillColor(sf::Color::Black);

    jobPay.setString("$???");
    jobPay.setFont(Globals::defaultFont);
    jobPay.setFillColor(sf::Color::Black);
    jobPay.setPosition(0, widthHeight.y/2);
}

sf::Vector2f WorldWideWeb::JobButton::getDimensions() {
    return widthHeight;
}

void WorldWideWeb::JobButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(jobTitle, states);
    target.draw(jobPay, states);
}

void WorldWideWeb::JobButton::mouseDown(sf::Event::MouseButtonEvent event) {
    sf::Vector2f eventPosition(event.x, event.y);

    if (background.getGlobalBounds().contains(eventPosition)) {
        JobSystem::JobHandler::getInstance()->loadJob(job);
        // Should get a new job because job is deleted when finished
        job = JobSystem::Factories::genericJob();
    }
}

void WorldWideWeb::JobButton::setPosition(float x, float y) {
    background.setPosition(x, y);
    jobTitle.setPosition(x, y);
    jobPay.setPosition(x, y+widthHeight.y/2);
}