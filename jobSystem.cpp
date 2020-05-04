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
        /*else {
            Globals::hackerWindow->updateList(currentJob->nextCharToDisplay());
            currentJob->keyPressed();
        }*/
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

            sf::String getNameString() {
                return "Normal Job";
            }

            sf::String getRewardString() {
                return "approx. $0.2-1 Big";
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
                Complication::FireWall* f = new Complication::FireWall(100, sf::seconds(10.f), sf::seconds(5.f), 10, 0.0);
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
                if(inputsRemainingToComplete > 0) {
                    std::cout << "Job failed! "<< inputsRemainingToComplete << " inputs left to complete!\n";
                }
                else {
                    // Give a reward...
                    std::cout << "Firewall job complete!" << std::endl;
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

            sf::String getNameString() {
                return "Hack NotHack Demo";
            }

            sf::String getRewardString() {
                return "The full game?";
            }
    };


    class ProcedurallyGeneratedJob : public JobSystem::JobInstance {
        private:
            int inputsRemainingToComplete;
            int inputs;
            bool isFinished;

            sf::String name;

        public:
            ProcedurallyGeneratedJob(int numInputs, int numComplications, float timeScale, std::string filePath)
                : JobInstance(filePath)
            {
                inputsRemainingToComplete = numInputs;
                inputs = 0;
                isFinished = false;

                std::cout << "Making new procedurally generated job...\n";

                if(numComplications > 0) {
                    int maxComp = numInputs/numComplications;
                    int minComp = (numInputs/numComplications)/4;
                    std::cout << "PGJob:: num inputs: " << numInputs << " , numComplications: " << numComplications << " , max complication input: " << maxComp << " , min comp input: "<< minComp << "\n";  
                    assert(Complication::ComplicationFactories::generateFirewalls(complications, numInputs, numComplications, maxComp, minComp, timeScale));
                    std::cout << "PGJob:: length of complications list: " << complications.size() << "\n";
                }

                name = JobSystem::jobNames[JobSystem::Factories::randomFromRange(0, sizeof(JobSystem::jobNames))/sizeof(JobSystem::jobNames[0])];

            }

             ~ProcedurallyGeneratedJob() {
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
                if(inputsRemainingToComplete > 0) {
                    std::cout << "Job failed! "<< inputsRemainingToComplete << " inputs left to complete!\n";
                }
                else {
                    // Give a reward...
                    std::cout << "Procedurally Generated job complete!" << std::endl;
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

            sf::String getNameString() {
                return name;
            }

            sf::String getRewardString() {
                return "$"+inputs;
            }
    };

    class OutroJob : public JobSystem::JobInstance { 
        private:
            int inputsRemainingToComplete;
            int inputs;
            bool isFinished;

        public:
            OutroJob()
                : JobInstance("last_job.txt")
            {
                inputsRemainingToComplete = 1602;
                //inputsRemainingToComplete = 1;
                inputs = 0;
                isFinished = false;
                Complication::FireWall* f = new Complication::FireWall(134, sf::seconds(10.f), sf::seconds(5.f), 154, 0.0);
                Complication::FireWall* f1 = new Complication::FireWall(334, sf::seconds(15.f), sf::seconds(5.f), 410, 0.0);
                Complication::FireWall* f2 = new Complication::FireWall(619, sf::seconds(20.f), sf::seconds(5.f), 945, 0.0);
                complications.push_back(dynamic_cast<Complication::Complication*>(f));
                complications.push_back(dynamic_cast<Complication::Complication*>(f1));
                complications.push_back(dynamic_cast<Complication::Complication*>(f2));
            }

            ~OutroJob() {
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
                if(inputsRemainingToComplete > 0) {
                    std::cout << "Job failed! "<< inputsRemainingToComplete << " inputs left to complete!\n";
                }
                else {
                    // Give a reward...
                    std::cout << "Last job complete!" << std::endl;
                    Globals::game->startOutro();
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

            sf::String getNameString() {
                return "Hack the NotHack Demo";
            }

            sf::String getRewardString() {
                return "The full game?";
            }
    };



}

JobSystem::JobInstance* JobSystem::Factories::genericJob() {
    return new GenericJob("hello-world.txt");
}

JobSystem::JobInstance* JobSystem::Factories::fireWallTestJob() {
    return new FireWallTestJob("hello-world.txt");
}


JobSystem::JobInstance* JobSystem::Factories::testPGJob() {
    return new ProcedurallyGeneratedJob(400, 2, 20.f, "hello-world.txt");
}


int JobSystem::Factories::randomFromRange(int min, int max) {
    return (rand() % (max-min)+1) + min;
}

JobSystem::JobInstance* JobSystem::Factories::easyRandomJob() {
    int numKeys = randomFromRange(20, 100);
    int numComplications = 0;
    int complicationTimeScale = 0.f;
    return new ProcedurallyGeneratedJob(numKeys, numComplications, complicationTimeScale, "hello-world.txt");
}


JobSystem::JobInstance* JobSystem::Factories::mediumRandomJob() {
    int numKeys = randomFromRange(100, 250);
    int numComplications = 1;
    int complicationTimeScale = 10.f;
    return new ProcedurallyGeneratedJob(numKeys, numComplications, complicationTimeScale, "hello-world.txt");
}


JobSystem::JobInstance* JobSystem::Factories::hardRandomJob() {
    int numKeys = randomFromRange(250, 500);
    int numComplications = randomFromRange(1,2);
    int complicationTimeScale = 20.f;
    return new ProcedurallyGeneratedJob(numKeys, numComplications, complicationTimeScale, "hello-world.txt");
}

JobSystem::JobInstance* JobSystem::Factories::mediumOrHardRandomJob() {
    if (randomFromRange(0, 10) <= 7) {
        return mediumRandomJob();
    } else {
        return hardRandomJob();
    }
}

JobSystem::JobInstance* JobSystem::Factories::storyJob() {
    return new OutroJob();
}