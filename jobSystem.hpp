#pragma once
#include <SFML/Graphics.hpp>
#include "singleton.hpp"
#include "eventSystem.hpp"
#include "complication.hpp"
#include "globals.hpp"
#include <string>
#include <list>
#include <cassert>

/************************
 * Namespace for all classes related
 * to the hacking jobs.
 ************************/
namespace JobSystem {
    sf::String jobNames[] = {"Fix HackTube", "Contract Trace Virus", "Scrub HackSpace Presence",
                             "Program More RAM", "Download a Car", "Catch Web Surfers",
                             "Make the Web Less Extreme", "Make the Web More Xtreme (dude)!",
                             "Connect the Uplink to the Download", "Defeat Dr. Wiwy",
                             "Make Ukelele Cat Popular", "Leak the Presidents Hax Returns",
                             "Locate Security Holes", "Mother 3 When?", "Hack the Gibson Supercomputer",
                             "Steal the Leo Virus", "Challenge WHOPR to Tic-Tac-Toe",
                             "Beat the MCP at Virtual Frisbee",
                             "Crack All of Modern Encryption", "Fix Modern Encryption", "Remove the Ghost from the Shell",
                             "Hack Kung Fu Skills into The Uno", "Erik Wrote These"};

    class JobInstance;

    /****************************************
     * Class respoonsible for changing jobs
     * and updating state
     ****************************************/
    class JobHandler : public Singleton<JobHandler>, public EventSystem::KeyPressedObserver {
        friend JobHandler* Singleton<JobHandler>::getInstance();

        private:
            JobInstance* currentJob;

        public:
            ~JobHandler();

            void loadJob(JobInstance*);
            bool isComplete(); // Is the current job complete?
            void finish(); // Called the finish function on the job and cleans up
            char nextCharToDisplay(); // Display the next character from the dummy text file
            void update(sf::Time); // Called every frame for time-related events

            /*EventSystem*/
            void keyPressed(sf::Event::KeyEvent);

        private:
            JobHandler(); // Should never be called
            void* operator new(size_t); // Should never be called
    };

    /***************************************
     * An instance of a particular job type,
     * used by JobHandler to represent a
     * job in progress
     ***************************************/
    class JobInstance {
        private:
            std::ifstream programTextFile; // Dummy text file to display text from

        protected:
            std::list<Complication::Complication*> complications; // All complications (ex. firewalls) in the job

        public:
            JobInstance(std::string);
            virtual ~JobInstance();

            char nextCharToDisplay(); // Return the next character that should be displayed from programTextFile

            virtual void keyPressed() = 0; // Not an observer
            virtual void finish() = 0; // Ends job, gives reward, and sets flags
            virtual void update(sf::Time) = 0; // Standard update function
            virtual bool isComplete() = 0; // Checks if job has ended

            virtual sf::String getNameString() = 0; // Get the name of the job (for display purposes)
            virtual sf::String getRewardString() = 0; // Get a description of the job's reward (for display purposes)
    };
    
    /**************************************
     * Factories for creating JobInstances
     **************************************/
    namespace Factories {

        JobInstance* genericJob(); // Returns a generic, easy job
        JobInstance* fireWallTestJob(); // Returns a job with a firewall

        JobInstance* testPGJob(); // Test function for Procedurally Generated Jobs

        JobInstance* easyRandomJob(); // Generates an easy job.
        JobInstance* mediumRandomJob(); // Generates a hard job.
        JobInstance* hardRandomJob(); // Generates a medium job.
        JobInstance* mediumOrHardRandomJob(); // Generates a medium or a hard job.
        JobInstance* storyJob(); // Returns the LastJob of the demo

        int randomFromRange(int min, int max); // Returns a random integer from the range specified
    }

}