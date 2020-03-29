#include "JobSystem.hpp"
#include "hackerWindow.h"
#include <iostream>

JobSystem::JobHandler::JobHandler() { }

void* JobSystem::JobHandler::operator new(size_t size) {
    return malloc(size);
}

void JobSystem::JobHandler::loadJob(JobInstance* jobPointer) {
        currentJob = jobPointer;
}

bool JobSystem::JobHandler::isComplete() {
    return currentJob->isComplete();
}

void JobSystem::JobHandler::finish() {
    currentJob->finish();

    // SHOULD BE FINAL CODE EXECUTE DURING ITERATION OF JOBHANDLER
    // WILL CAUSE SEG-FAULTS OTHERWISE DUE TO NULL-POINTER
    delete currentJob;
    currentJob = 0;
}

char JobSystem::JobHandler::nextCharToDisplay() {
    return currentJob->nextCharToDisplay();
}

/*EventSystem*/
void JobSystem::JobHandler::keyPressed(sf::Event::KeyEvent event) {
    if (currentJob != 0) {
        Globals::hackerWindow->updateList(currentJob->nextCharToDisplay());
        currentJob->keyPressed();

        if (isComplete()) {
            finish();
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
                inputsRemainingToComplete = 20;
            }

            void keyPressed() {
                inputsRemainingToComplete--;
            }

            void finish() {
                // Give a reward...
                std::cout << "Generic job complete!" << std::endl;
            }

            bool isComplete() {
                return inputsRemainingToComplete <= 0;
            }
    };
}

JobSystem::JobInstance* JobSystem::Factories::genericJob() {
    return new GenericJob("hello-world.txt");
}