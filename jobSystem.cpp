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


    /******************************************************************************
     * FireWallTestJob:                                                           *
     *      -A medium difficulty job containing a single firewall.                *
     *      -Derived class of JobInstance.                                        *
     ******************************************************************************/
    class FireWallTestJob : public JobSystem::JobInstance { 
        private:
            int inputsRemainingToComplete;
            int inputs;
            bool isFinished;

        public:
            /******************************************************************************
             * FireWallTestJob Constructor -- Constructor for creating a new instance.    *
             * Parameters:                                                                *
             *      -filePath: A string pointing to the txt file to be displayed during   *
             *       the job.                                                             *
             ******************************************************************************/
            FireWallTestJob(std::string filePath)
                : JobInstance(filePath)
            {
                inputsRemainingToComplete = 200;
                inputs = 0;
                isFinished = false;
                Complication::FireWall* f = new Complication::FireWall(100, sf::seconds(10.f), sf::seconds(5.f), 10, 0.0);
                complications.push_front(dynamic_cast<Complication::Complication*>(f));
            }

            /******************************************************************************
             * FireWallTestJob Deconstructor -- Deconstructor for destroying an instance. *
             *      Deletes all the complications attached to the job.                    *
             ******************************************************************************/
            ~FireWallTestJob() {
                for (Complication::Complication* c : complications) {
                    delete c;
                }
            }

            /******************************************************************************
             * keyPressed -- Reacts to key input, and finishes the job or activates       *
             *      complications based on how many keys have been input. Also calls the  *
             *      complications' methods of the same name.                              *
             *      -Overrides JobInstance method, not an event system observer.          *
             ******************************************************************************/
            void keyPressed() {
                inputsRemainingToComplete--;
                inputs++;
                if(inputsRemainingToComplete == 0) isFinished = true;
                else { 
                    // Iterate through all the complications. Activate any that have the required number of inputs.
                    for (Complication::Complication* c : complications) {
                        if (!c->isActive() && !c->getEndData().ended && inputs >= c->getNumberKeysRequired()) {
                            std::cout << c->getNumberKeysRequired() << " , " << inputs;
                            c->startComplication();
                        }
                        else c->keyPressed();
                    }
                }
            }

            /******************************************************************************
             * finish -- Called by the JobHandler when the job is ended. Gives message    *
             *      on job success or failure.                                            *
             ******************************************************************************/
            void finish() {
                if(inputsRemainingToComplete > 0) {
                    std::cout << "Job failed! "<< inputsRemainingToComplete << " inputs left to complete!\n";
                }
                else {
                    // Give a reward...
                    std::cout << "Firewall job complete!" << std::endl;
                }
            }

            /******************************************************************************
             * update -- Called every frame. Calls update on the complications, ends the  *
             *      job by marking "isFinished" if any complication successfully          *
             *      completes.
             * Parameters:                                                                *
             *      -deltaTime: the time since the last frame.                            *
             ******************************************************************************/
            void update(sf::Time deltaTime) {
                /* Iterate through all the complications. 
                Check if any are done, and if the job has been failed. 
                Stop the job if it has been failed.*/
                for (Complication::Complication* c : complications) {
                    c->update(deltaTime);
                    Complication::endData cData = c->getEndData();
                    if (cData.ended && !cData.defeated) {
                        isFinished = true;
                        break;
                    }
                }
            }

            /******************************************************************************
             * isComplete -- Getter method for whether or not the job is complete.        *
             *      -Used by job handler to determine when a job is done.                 *
             * Returns:                                                                   *
             *      -True if the job is finished.                                         *
             *      -False if the job is not finished.                                    *
             ******************************************************************************/
            bool isComplete() {
                return isFinished;
            }

            /******************************************************************************
             * getNameString -- Getter method for the name of the job.                    *
             *      -Used by job buttons on Hackdeed.                                     *
             * Returns:                                                                   *
             *      -The name of the job, "Firewall Test"                                 *
             ******************************************************************************/
            sf::String getNameString() {
                return "Firewall Test";
            }

            /******************************************************************************
             * getRewardString -- Getter method for the reward of the job.                *
             *      -Used by job buttons on Hackdeed.                                     *
             * Returns:                                                                   *
             *      -The reward of the job, "Satisfaction"                                *
             ******************************************************************************/
            sf::String getRewardString() {
                return "Satisfaction";
            }
    };


    /******************************************************************************
     * ProcedurallyGeneratedJob:                                                  *
     *      -A special type of job that takes multiple parameters and generates a *
     *        unique job out of them.                                             *
     *      -Derived class of JobInstance.                                        *
     ******************************************************************************/
    class ProcedurallyGeneratedJob : public JobSystem::JobInstance {
        private:
            int inputsRemainingToComplete;
            int inputs;
            bool isFinished;

            sf::String name;

    
        public:
            /******************************************************************************
             * ProcedurallyGeneratedJob Constructor -- Constructor for creating a new     *
             *      instance.                                                             *
             * Parameters:                                                                *
             *      -numInputs: The integer number of key inputs needed to finish the job.*
             *      -numComplications: The integer number of complications the job should *
             *        have.                                                               * 
             *      -timeScale: The float used to determine the amount of seconds per key *
             *        the player is expected to input. Used for complication generation.  *
             *      -filePath: A string pointing to the txt file to be displayed during   *
             *       the job.                                                             *
             *      -difficulty: The string containing the job difficulty.                *
             ******************************************************************************/
            ProcedurallyGeneratedJob(int numInputs, int numComplications, float timeScale, std::string filePath, std::string difficulty)
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
                name = difficulty + ": " + name;
            }   

             
            /******************************************************************************
             * ProcedurallyGeneratedJob Deconstructor -- Deconstructor for destroying an  *
             *      instance. Deletes all the complications attached to the job.          *
             ******************************************************************************/
             ~ProcedurallyGeneratedJob() {
                for (Complication::Complication* c : complications) {
                    delete c;
                }
            }

            /******************************************************************************
             * keyPressed -- Reacts to key input, and finishes the job or activates       *
             *      complications based on how many keys have been input. Also calls the  *
             *      complications' methods of the same name.                              *
             *      -Overrides JobInstance method, not an event system observer.          *
             ******************************************************************************/
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

            
            /******************************************************************************
             * finish -- Called by the JobHandler when the job is ended. Gives message    *
             *      on job success or failure.                                            *
             ******************************************************************************/
            void finish() {
                if(inputsRemainingToComplete > 0) {
                    std::cout << "Job failed! "<< inputsRemainingToComplete << " inputs left to complete!\n";
                }
                else {
                    // Give a reward...
                    std::cout << "Procedurally Generated job complete!" << std::endl;
                }
            }


            /******************************************************************************
             * update -- Called every frame. Calls update on the complications, ends the  *
             *      job by marking "isFinished" if any complication successfully          *
             *      completes.
             * Parameters:                                                                *
             *      -deltaTime: the time since the last frame.                            *
             ******************************************************************************/
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

            /******************************************************************************
             * isComplete -- Getter method for whether or not the job is complete.        *
             *      -Used by job handler to determine when a job is done.                 *
             * Returns:                                                                   *
             *      -True if the job is finished.                                         *
             *      -False if the job is not finished.                                    *
             ******************************************************************************/
            bool isComplete() {
                return isFinished;
            }

            /******************************************************************************
             * getNameString -- Getter method for the name of the job.                    *
             *      -Used by job buttons on Hackdeed.                                     *
             * Returns:                                                                   *
             *      -The name of the job, randomly determined per instance from name pool *
             ******************************************************************************/
            sf::String getNameString() {
                return name;
            }

            /******************************************************************************
             * getRewardString -- Getter method for the reward of the job.                *
             *      -Used by job buttons on Hackdeed.                                     *
             * Returns:                                                                   *
             *      -The reward of the job, a monetary amount = the number of key inputs. *
             ******************************************************************************/
            sf::String getRewardString() {
                return "$"+inputs;
            }
    };


    /******************************************************************************
     * OutroJob:                                                                  *
     *      -A unique, story based job with Expert level difficulty that serves   *
     *       as the final level of the demo. Has 1604 key inputs and 3 firewalls, *
     *       as well as a unique, dedicated text file.                            *
     *      -Derived class of JobInstance.                                        *
     ******************************************************************************/
    class OutroJob : public JobSystem::JobInstance { 
        private:
            int inputsRemainingToComplete;
            int inputs;
            bool isFinished;

        public:
            /******************************************************************************
             * OutroJob Constructor -- Constructor for creating a new instance.           *
             ******************************************************************************/
            OutroJob()
                : JobInstance("last_job.txt")
            {
                inputsRemainingToComplete = 1604;
                //inputsRemainingToComplete = 1; // Debug
                inputs = 0;
                isFinished = false;  

                //initialize firewalls 
                Complication::FireWall* f = new Complication::FireWall(134, sf::seconds(10.f), sf::seconds(5.f), 154, 0.0);
                Complication::FireWall* f1 = new Complication::FireWall(334, sf::seconds(15.f), sf::seconds(5.f), 410, 0.0);
                Complication::FireWall* f2 = new Complication::FireWall(619, sf::seconds(25.f), sf::seconds(5.f), 947, 0.0);
                complications.push_back(dynamic_cast<Complication::Complication*>(f));
                complications.push_back(dynamic_cast<Complication::Complication*>(f1));
                complications.push_back(dynamic_cast<Complication::Complication*>(f2));
            }

            /******************************************************************************
             * FireWallTestJob Deconstructor -- Deconstructor for destroying an instance. *
             *      Deletes all the complications attached to the job.                    *
             ******************************************************************************/
            ~OutroJob() {
                for (Complication::Complication* c : complications) {
                    delete c;
                }
            }

            /******************************************************************************
             * keyPressed -- Reacts to key input, and finishes the job or activates       *
             *      complications based on how many keys have been input. Also calls the  *
             *      complications' methods of the same name.                              *
             *      -Overrides JobInstance method, not an event system observer.          *
             ******************************************************************************/
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

            /******************************************************************************
             * finish -- Called by the JobHandler when the job is ended. Gives message    *
             *      on job success or failure, starts the outro on a success.             *
             ******************************************************************************/
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


            /******************************************************************************
             * update -- Called every frame. Calls update on the complications, ends the  *
             *      job by marking "isFinished" if any complication successfully          *
             *      completes.
             * Parameters:                                                                *
             *      -deltaTime: the time since the last frame.                            *
             ******************************************************************************/
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

            /******************************************************************************
             * isComplete -- Getter method for whether or not the job is complete.        *
             *      -Used by job handler to determine when a job is done.                 *
             * Returns:                                                                   *
             *      -True if the job is finished.                                         *
             *      -False if the job is not finished.                                    *
             ******************************************************************************/
            bool isComplete() {
                return isFinished;
            }

            /******************************************************************************
             * getNameString -- Getter method for the name of the job.                    *
             *      -Used by job buttons on Hackdeed.                                     *
             * Returns:                                                                   *
             *      -The name of the job, "Expert: Hack the NotHack Demo"                 *
             ******************************************************************************/
            sf::String getNameString() {
                return "Expert: Hack the NotHack Demo";
            }


            /******************************************************************************
             * getRewardString -- Getter method for the reward of the job.                *
             *      -Used by job buttons on Hackdeed.                                     *
             * Returns:                                                                   *
             *      -The reward of the job, "The full game?"                              *
             ******************************************************************************/
            sf::String getRewardString() {
                return "The full game?";
            }
    };



}

/******************************************************************************
 * genericJob -- A factory method for making generic jobs.                    *
 * Returns:                                                                   *
 *      -A new instance of a GenericJob                                       *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::genericJob() {
    return new GenericJob("hello-world.txt");
}

/******************************************************************************
 * fireWallTestJob -- A factory method for making FireWallTestJobs.           *
 * Returns:                                                                   *
 *      -A new instance of a FireWallTestJob                                  *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::fireWallTestJob() {
    return new FireWallTestJob("hello-world.txt");
}

/******************************************************************************
 * testPGJob -- A factory method for making test ProcedurallyGeneratedJobs.   *
 * Returns:                                                                   *
 *      -A new instance of a ProcedurallyGeneratedJob                         *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::testPGJob() {
    return new ProcedurallyGeneratedJob(400, 2, 20.f, "hello-world.txt", "med");
}

/******************************************************************************
 * randomFromRange -- Generates a random number from an input range.          *
 * Parameters:                                                                *
 *      -min: An integer representing the minimum value of the range.         *
 *      -max: An integer representing the maximum value of the range.         *
 * Returns:                                                                   *
 *      -A random integer with a value between min and max.                   *
 ******************************************************************************/
int JobSystem::Factories::randomFromRange(int min, int max) {
    return (rand() % (max-min)+1) + min;
}

/******************************************************************************
 * easyRandomJob -- A factory method for making easy ProcedurallyGeneratedJob *
 * Returns:                                                                   *
 *      -A new instance of a ProcedurallyGeneratedJob with 20-100 key inputs  *
 *        and no complications.                                               *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::easyRandomJob() {
    int numKeys = randomFromRange(20, 100);
    int numComplications = 0;
    int complicationTimeScale = 0.f;
    return new ProcedurallyGeneratedJob(numKeys, numComplications, complicationTimeScale, "hello-world.txt", "Easy");
}

/******************************************************************************
 * mediumRandomJob -- A factory method for making medium                      *
 *      ProcedurallyGeneratedJobs.                                            *
 * Returns:                                                                   *
 *      -A new instance of a ProcedurallyGeneratedJob with 100-250 key inputs *
 *        and 1 complication.                                                 *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::mediumRandomJob() {
    int numKeys = randomFromRange(100, 250);
    int numComplications = 1;
    int complicationTimeScale = 10.f;
    return new ProcedurallyGeneratedJob(numKeys, numComplications, complicationTimeScale, "hello-world.txt", "Medium");
}


/******************************************************************************
 * hardRandomJob -- A factory method for making hard ProcedurallyGeneratedJob *
 * Returns:                                                                   *
 *      -A new instance of a ProcedurallyGeneratedJob with 250-500 key inputs *
 *        and 1-2 complications                                               *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::hardRandomJob() {
    int numKeys = randomFromRange(250, 500);
    int numComplications = randomFromRange(1,2);
    int complicationTimeScale = 20.f;
    return new ProcedurallyGeneratedJob(numKeys, numComplications, complicationTimeScale, "hello-world.txt", "Hard");
}
/******************************************************************************
 * mediumOrHardRandomJob -- A factory method for making a medium or a hard    *
 *      ProcedurallyGeneratedJob, determined at random with a medium bias.    *
 * Returns:                                                                   *
 *      -A medium or hard ProcedurallyGeneratedJob.                           *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::mediumOrHardRandomJob() {
    if (randomFromRange(0, 10) <= 7) {
        return mediumRandomJob();
    } else {
        return hardRandomJob();
    }
}


/******************************************************************************
 * storyJob -- A factory method for making outro jobs.                        *
 * Returns:                                                                   *
 *      -A new instance of an OutroJob                                        *
 ******************************************************************************/
JobSystem::JobInstance* JobSystem::Factories::storyJob() {
    return new OutroJob();
}