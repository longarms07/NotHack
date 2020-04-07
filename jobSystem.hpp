#pragma once
#include <SFML/Graphics.hpp>
#include "singleton.hpp"
#include "eventSystem.hpp"
#include "complication.hpp"
#include <string>
#include <list>

namespace JobSystem {
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
            
    };

    namespace Factories {
        JobInstance* genericJob();
        JobInstance* fireWallTestJob();
    }

}