#include "worldWideWeb.hpp"
#include "eventSystem.hpp"
#include "globals.hpp"
#include <iostream>
#include <string>

/****************
 * BrowserWindow
 ****************/

/************************
 * Parameters:
 *  - sf::Vector2f anchorPoint: Screen coordinates to anchor the window
 *  - sf::Vector2f widthHeightScale: dimensions of the browser window, in % of the screen size
 *  - sf::Font& font: Font to use for text
 ************************/
WorldWideWeb::BrowserWindow::BrowserWindow(sf::Vector2f anchorPoint, sf::Vector2f widthHeightScale, sf::Font& font)
    : hackscapeSprite(),
      monitorOffset(204.f, 85.f),
      urlOffset(58.f, 25.f),
      websiteOffset(38.f, 150.f),
      EventSystem::MouseDownObserver(false),
      EventSystem::MouseMoveObserver(false),
      EventSystem::KeyPressedObserver(false)
{
    currentSite = NULL;

    hackscapeSprite.setTexture(Globals::computerSpriteSheet);
    hackscapeSprite.setTextureRect(sf::IntRect(979, 492, 312, 237));
    hackscapeSprite.setPosition(monitorOffset+anchorPoint);
    hackscapeSprite.setScale(widthHeightScale);

    urlBar = new URLBar(font);
    urlBar->setPosition(urlOffset.x+monitorOffset.x+anchorPoint.x, urlOffset.y+monitorOffset.y+anchorPoint.y);
    setWebsite(WorldWideWeb::Sites::Red::getInstance());

    dragging = false;
}

WorldWideWeb::BrowserWindow::~BrowserWindow() {
    delete urlBar;
}

void WorldWideWeb::BrowserWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(hackscapeSprite, states);

    target.draw(*urlBar, states);
    target.draw(*currentSite, states);
}

void WorldWideWeb::BrowserWindow::setPosition(float x, float y) {
    hackscapeSprite.setPosition(monitorOffset.x+x, monitorOffset.x+x);
    urlBar->setPosition(urlOffset.x+monitorOffset.x+x, urlOffset.y+monitorOffset.y+y);
    setWebsitePosition();
}

// When a website is loaded, its position should be set to the position of the computer/browser
void WorldWideWeb::BrowserWindow::setWebsitePosition() {
    sf::Vector2f newSitePosition = monitorOffset+websiteOffset;
    currentSite->setPosition(newSitePosition.x, newSitePosition.y);
}

// Deprecated
void WorldWideWeb::BrowserWindow::mouseMove(sf::Event::MouseMoveEvent event) {
    // if (dragging) {
    //     sf::Vector2f eventLocation(event.x, event.y);
    //     sf::Vector2f newPosition = eventLocation - mouseOffsetFromOrigin;
    //     setPosition(newPosition.x, newPosition.y);
    // }
}

// Deprecated
void WorldWideWeb::BrowserWindow::mouseDown(sf::Event::MouseButtonEvent event) {
    // sf::Vector2f eventLocation(event.x, event.y);

    // if (windowBackground.getGlobalBounds().contains(eventLocation)) {
    //     // std::cout << "Mouse down in bounds" << std::endl;
    //     mouseOffsetFromOrigin = eventLocation - windowBackground.getPosition();
    //     dragging = true;
    // } else {
    //     // std::cout << "Mouse down outside bounds" << std::endl;
    // }
}

// If return is pressed and the URLBar is focused, load the website URL (if valid)
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

// Deprecated
void WorldWideWeb::BrowserWindow::mouseUp(sf::Event::MouseButtonEvent event) {
    // std::cout << "Mouse up event" << std::endl;
    dragging = false;
}


// Set the current website to the provided pointer; deactive the old website
void WorldWideWeb::BrowserWindow::setWebsite(WindowPart* newSite) {
    if (currentSite != NULL) {
        currentSite->deactivate();
    }

    currentSite = newSite;
    setWebsitePosition();
    currentSite->activate();
}

// Register the BrowserWindow to be displayed
void WorldWideWeb::BrowserWindow::activate() {
    RenderSystem::RenderHandler::getInstance()->registerDrawable(this);
    EventSystem::EventHandler* handlerInstance = EventSystem::EventHandler::getInstance();
    handlerInstance->registerMouseMoveObserver(this);
    handlerInstance->registerMouseDownObserver(this);
    handlerInstance->registerKeyPressedObserver(this);
    urlBar->activate();
    currentSite->activate();
}

// Unregister the BrowserWindow from event and render handling
void WorldWideWeb::BrowserWindow::deactivate() {
    RenderSystem::RenderHandler::getInstance()->unregisterDrawable(this);
    EventSystem::EventHandler* handlerInstance = EventSystem::EventHandler::getInstance();
    handlerInstance->unregisterMouseMoveObserver(this);
    handlerInstance->unregisterMouseDownObserver(this);
    handlerInstance->unregisterKeyPressedObserver(this);
    urlBar->deactivate();
    currentSite->deactivate();
}


/****************
 * URLBar
 ****************/
WorldWideWeb::URLBar::URLBar(sf::Font& font)
    : textField(sf::Vector2f(0.f, 0.f), sf::Vector2f(186.f, 17.f), font)
{ }

void WorldWideWeb::URLBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(textField, states);
}

void WorldWideWeb::URLBar::setPosition(float x, float y) {
    textField.setPosition(x, y);
}

// Register the URLBar to the EventSystem
void WorldWideWeb::URLBar::activate() {
    EventSystem::EventHandler* handlerInstance = EventSystem::EventHandler::getInstance();
    handlerInstance->registerMouseDownObserver(&textField);
    handlerInstance->registerTextEnteredObserver(&textField);
    handlerInstance->registerKeyPressedObserver(&textField);
}

// Unregister the URLBar from the EventSystem
void WorldWideWeb::URLBar::deactivate() {
    EventSystem::EventHandler* handlerInstance = EventSystem::EventHandler::getInstance();
    handlerInstance->unregisterMouseDownObserver(&textField);
    handlerInstance->unregisterTextEnteredObserver(&textField);
    handlerInstance->unregisterKeyPressedObserver(&textField);
}


/************
 * Red testing website
 ************/
WorldWideWeb::Sites::Red::Red()
    : background()
{
    background.setSize(sf::Vector2f(235.f, 132.f));
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


/************
 * Blue testing website
 ************/

WorldWideWeb::Sites::Blue::Blue()
    : background()
{
    background.setSize(sf::Vector2f(235.f, 132.f));
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


/************
 * Hackdeed job board website
 ************/

/*************
 * In addition to the website,
 * three job buttons are instantiated
 *************/
WorldWideWeb::Sites::Hackdeed::Hackdeed()
    : background(),
      buttonOffset(6.f, 10.f)
{
    background.setSize(sf::Vector2f(235.f, 132.f));
    background.setFillColor(sf::Color::Yellow);

    // Initialize buttons
    jobButtons.push_back(new JobButton(sf::Vector2f(220.f, 32.f), JobSystem::Factories::easyRandomJob()));
    jobButtons.push_back(new JobButton(sf::Vector2f(220.f, 32.f), JobSystem::Factories::mediumRandomJob()));
    jobButtons.push_back(new JobButton(sf::Vector2f(220.f, 32.f), JobSystem::Factories::storyJob()));
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
        jobButton->setPosition(buttonOffset.x+x, buttonOffset.y+y+(i*5)+(i*jobButton->getDimensions().y));
        i++;
    }
}

// Call activate() for all jobButtons; registers buttons for event handling
void WorldWideWeb::Sites::Hackdeed::activate() {
    for (JobButton* jobButton : jobButtons) {
        jobButton->activate();
    }
}

// Call deactivate() for all jobButtons; unregisters buttons for event handling
void WorldWideWeb::Sites::Hackdeed::deactivate() {
    for (JobButton* jobButton : jobButtons) {
        jobButton->deactivate();
    }
}

/*************
 * JobButton
 *************/

/*****************
 * Parameters:
 *  - sf::Vector2f pWidthHeight: Dimensions of the button
 *  - JobInstance* instance: Job that will be loaded when the button is clicked
 *****************/
WorldWideWeb::JobButton::JobButton(sf::Vector2f pWidthHeight, JobSystem::JobInstance* instance)
    : background(pWidthHeight),
      MouseDownObserver(false)
{
    widthHeight = pWidthHeight;

    job = instance;

    jobTitle.setFont(Globals::defaultFont);
    jobTitle.setCharacterSize(10);
    jobTitle.setFillColor(sf::Color::Black);
    jobPay.setPosition(5, 0);

    jobPay.setFont(Globals::defaultFont);
    jobPay.setCharacterSize(10);
    jobPay.setFillColor(sf::Color::Black);
    jobPay.setPosition(5, widthHeight.y/2);

    loadStrings();
}

// Display the name and reward strings on the button
// Note: This should be called after JobButton::job is changed
void WorldWideWeb::JobButton::loadStrings() {
    jobTitle.setString(job->getNameString());
    jobPay.setString(job->getRewardString());
}

sf::Vector2f WorldWideWeb::JobButton::getDimensions() {
    return widthHeight;
}

void WorldWideWeb::JobButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(jobTitle, states);
    target.draw(jobPay, states);
}

// Detect if button was clicked
void WorldWideWeb::JobButton::mouseDown(sf::Event::MouseButtonEvent event) {
    sf::Vector2f eventPosition(event.x, event.y);

    if (background.getGlobalBounds().contains(eventPosition)) {
        JobSystem::JobHandler::getInstance()->loadJob(job);
        // Should get a new job because job is deleted when finished
        job = JobSystem::Factories::mediumOrHardRandomJob();
        loadStrings();
    }
}

void WorldWideWeb::JobButton::setPosition(float x, float y) {
    background.setPosition(x, y);
    jobTitle.setPosition(5+x, y);
    jobPay.setPosition(5+x, y+widthHeight.y/2);
}

// Register the button for event handling
void WorldWideWeb::JobButton::activate() {
    EventSystem::EventHandler* handlerInstance = EventSystem::EventHandler::getInstance();
    handlerInstance->registerMouseDownObserver(this);
}

// Unregister the button from event handling
void WorldWideWeb::JobButton::deactivate() {
    EventSystem::EventHandler* handlerInstance = EventSystem::EventHandler::getInstance();
    handlerInstance->unregisterMouseDownObserver(this);
}