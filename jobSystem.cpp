#include "jobSystem.hpp"
#include "hackerWindow.h"
#include <iostream>

JobSystem::JobHandler::JobHandler() {
    currentJob = NULL;
}

JobSystem::JobHandler::~JobHandler() {
    if (currentJob != NULL) {
        delete currentJob;
    }
}

void* JobSystem::JobHandler::operator new(size_t size) {
    return malloc(size);
}

void JobSystem::JobHandler::loadJob(JobInstance* jobPointer) {
        currentJob = jobPointer;
        Globals::game->activateWindow(Globals::hackerWindow);
}

bool JobSystem::JobHandler::isComplete() {
    return currentJob->isComplete();
}

void JobSystem::JobHandler::finish() {
    currentJob->finish();
    Globals::game->activateWindow(Globals::browserWindow);
    Globals::hackerWindow->clear();

    // SHOULD BE FINAL CODE EXECUTE DURING ITERATION OF JOBHANDLER
    // WILL CAUSE SEG-FAULTS OTHERWISE DUE TO NULL-POINTER
    delete currentJob;
    currentJob = NULL;
}

char JobSystem::JobHandler::nextCharToDisplay() {
    return currentJob->nextCharToDisplay();
}

void JobSystem::JobHandler::update(sf::Time deltaTime) {
    if (currentJob != 0) {
        currentJob->update(deltaTime);
    }
}

/*EventSystem*/
void JobSystem::JobHandler::keyPressed(sf::Event::KeyEvent event) {
    if (currentJob != NULL) {
        Globals::hackerWindow->updateList(currentJob->nextCharToDisplay());
        currentJob->keyPressed();
        if (isComplete()) {
            finish();
        }
        else {
            Globals::hackerWindow->updateList(currentJob->nextCharToDisplay());
            currentJob->keyPressed();
        }
    }
}

/*JobInstance*/
JobSystem::JobInstance::JobInstance(std::string filePath) {
    programTextFile.open(filePath);

    if (programTextFile.bad()) {
        std::cerr << "Failed to read file, exiting...\n";
        exit (8);
    }
}

JobSystem::JobInstance::~JobInstance() {
    programTextFile.close();
}

char JobSystem::JobInstance::nextCharToDisplay() {
    /*Exception Handling*/
    if (!programTextFile.is_open()) {
        std::cerr << "Tried to read from unopen stream...\n";
        exit (7); // TODO: set exit code
    }

    if (programTextFile.bad()) {
        std::cerr << "Error reading from file...\n";
        exit (8);
    }

    /*Getting next character*/
    if (programTextFile.eof()) { // Restart from beginning of file
        programTextFile.clear();
        programTextFile.seekg(0, std::ios::beg);
        return '\n'; // Put future text on a new line
    } else {
        char nextChar;
        programTextFile >> std::noskipws >> nextChar;
        return nextChar;
    }
}



/*Factory Methods*/
namespace { // Classes for factories to use
    class GenericJob : public JobSystem::JobInstance {
        private:
            int inputsRemainingToComplete;

        public:
            GenericJob(std::string filePath)
                : JobInstance(filePath)
            {
                inputsRemainingToComplete = 100;
            }

            void keyPressed() {
                inputsRemainingToComplete--;
            }

            void finish() {
                // Give a reward...
                std::cout << "Generic job complete!" << std::endl;
            }

            void update(sf::Time deltaTime) {
                //Stubbed, nothing to do here.
            }

            bool isComplete() {
                return inputsRemainingToComplete <= 0;
            }
    };

    class FireWallTestJob : public JobSystem::JobInstance { 
        private:
            int inputsRemainingToComplete;
            int inputs;
            bool isFinished;

        public:
            FireWallTestJob(std::string filePath)
                : JobInstance(filePath)
            {
                inputsRemainingToComplete = 200;
                inputs = 0;
                isFinished = false;
                Complication::FireWall* f = new Complication::FireWall(100, sf::seconds(1.f), sf::seconds(.5f), 10, 0.0);
                complications.push_front(dynamic_cast<Complication::Complication*>(f));
            }

            ~FireWallTestJob() {
                for (Complication::Complication* c : complications) {
                    delete c;
                }
            }

            void keyPressed() {
                inputsRemainingToComplete--;
                inputs++;
                if(inputsRemainingToComplete == 0) isFinished = true;
                else { 
                    for (Complication::Complication* c : complications) {
                        if (!c->isActive() && !c->getEndData().ended && inputs >= c->getNumberKeysRequired()) {
                            std::cout << c->getNumberKeysRequired() << " , " << inputs;
                            c->startComplication();
                        }
                        else c->keyPressed();
                    }
                }
            }

            void finish() {
                if(inputsRemainingToComplete != 0) {
                    std::cout << "Job failed!\n";
                }
                else {
                    // Give a reward...
                    std::cout << "Generic job complete!" << std::endl;
                }
            }

            void update(sf::Time deltaTime) {
                for (Complication::Complication* c : complications) {
                    c->update(deltaTime);
                    Complication::endData cData = c->getEndData();
                    if (cData.ended && !cData.defeated) {
                        isFinished = true;
                        break;
                    }
                }
            }

            bool isComplete() {
                return isFinished;
            }
    };

}

JobSystem::JobInstance* JobSystem::Factories::genericJob() {
    return new GenericJob("hello-world.txt");
}

JobSystem::JobInstance* JobSystem::Factories::fireWallTestJob() {
    return new FireWallTestJob("hello-world.txt");
}