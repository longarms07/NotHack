#pragma once
#include <SFML/Graphics.hpp>
#include "singleton.hpp"
#include "eventSystem.hpp"
#include "complication.hpp"
#include "globals.hpp"
#include <string>
#include <list>
#include <cassert>

namespace JobSystem {
    sf::String jobNames[] = {"Fix HackTube", "Contract Trace Virus", "Scrub HackSpace Presence",
                             "Program More RAM", "Download a Car", "Catch Web Surfers",
                             "Make the Web Less Extreme", "Make the Web More Xtreme (dude)!",
                             "Connect the Uplink to the Download", "Defeat Dr. Wiwy",
                             "Make Ukelele Cat Popular", "Leak the Presidents Hax Returns",
                             "Locate Security Holes", "Mother 3 When?", "Hack the Gibdaughter Supercomputer",
                             "Steal the Leo Virus", "Challenge Norad's Computer to Tic-Tac-Toe",
                             "Beat the Maverick Computer Program at Virtual Frisbee",
                             "Crack All of Modern Encryption", "Fix Modern Encryption", "Remove the Ghost from the Shell",
                             "Insert Kung Fu Skills into The Uno's Brain", "Erik Wrote These"};

    class JobInstance;

    class JobHandler : public Singleton<JobHandler>, public EventSystem::KeyPressedObserver {
        friend JobHandler* Singleton<JobHandler>::getInstance();

        private:
            JobInstance* currentJob;

        public:
            ~JobHandler();

            void loadJob(JobInstance*);
            bool isComplete();
            void finish();
            char nextCharToDisplay();
            void update(sf::Time);

            /*EventSystem*/
            void keyPressed(sf::Event::KeyEvent);

        private:
            JobHandler(); // Should never be called
            void* operator new(size_t); // Should never be called
    };

    class JobInstance {
        private:
            std::ifstream programTextFile;

        protected:
            std::list<Complication::Complication*> complications;

        public:
            JobInstance(std::string);
            virtual ~JobInstance();

            char nextCharToDisplay();

            virtual void keyPressed() = 0; // Not an observer
            virtual void finish() = 0; // Ends job, gives reward, and sets flags
            virtual void update(sf::Time) = 0; // Standard update function
            virtual bool isComplete() = 0; // Checks if job has ended

            virtual sf::String getNameString() = 0;
            virtual sf::String getRewardString() = 0;
    };

    namespace Factories {

        JobInstance* genericJob();
        JobInstance* fireWallTestJob();

        JobInstance* testPGJob();

        JobInstance* easyRandomJob();
        JobInstance* mediumRandomJob();
        JobInstance* hardRandomJob();
        JobInstance* mediumOrHardRandomJob();

        int randomFromRange(int min, int max);
    }

}