#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "progressBar.h"
#include "renderSystem.hpp"
#include "spriteAnimations.hpp"
#include <cstdlib>
 
namespace Complication {

    struct endData { // Used by JobSystem to check if a job has been ended 
        bool ended; // True if the job is ended, false if not
        bool defeated; // True if the player defeated the complication, false if the complication completed successfully
    };

    class Complication {
        public:
            virtual ~Complication() { };

            virtual void startComplication() = 0;
            virtual void endComplication(bool defeated) = 0; // Defines behavior for ending a complication. "defeated" is true if the player defeated the complication.
            virtual void keyPressed() = 0; // Not event system
            virtual void update(sf::Time deltaTime) = 0; // Standard update function called by JobInstance


            endData getEndData();  
            int getNumberKeysRequired(); // Getter method for the number of keys the complication expects to have
            double getPenaltyValue(); // Gets the monetary penalty of the job
            bool isActive(); // Returns whether or not the complication has been started

        protected:
            int numKeysReq; // Number of keyd the complication expects the hackerwindow to print before it is activated
            double penalty; // The monetary penalty of failure
            endData endingData; // The current endData of the complication
            bool active; // Whether or not the job has been started

    };

    class FireWall : public Complication, public sf::Drawable {
        private: 
            sf::Time elapsedTime; // The time the firewall has been active (the coolant subtracts time from it)
            sf::Time maximumTime; // The maximum time the firewall can be active before the mission is failed.
            sf::Time coolantTime; // The amount of time that applying a coolant removes from the firewall.
            int numTargetChars; // The number of characters that needs to be input before time runs out
            int numEnteredChars; // The number of characters that have been entered thus far
            
            sf::Vector2f maxAnchorPoint; // The highest possible anchor point, equal to the parent HackerWindow's anchorpoint
            sf::Vector2f minAnchorPoint; // The lowest possible anchor point, calculated from max and bounds
            sf::Vector2f maxBounds; // Maximum bounds of wallGraphic, equal to the bounds of HackerWindow. x is width, y is height.

            sf::Vector2f barOffset;
            sf::Vector2f firewallOffset;
            
            SpriteAnimations::HorizontalSine* fireLayer1; // Layers for fire graphic
            SpriteAnimations::HorizontalSine* fireLayer2;
            SpriteAnimations::HorizontalSine* fireLayer3;
            
            ProgressBar* progressBar;

        public:
            FireWall(int targetChars, sf::Time maxTime, sf::Time coolTime, int activationKeys, double penaltyAmount); 
            ~FireWall();

            virtual void startComplication();
            virtual void endComplication(bool defeated);
            virtual void keyPressed();
            virtual void update(sf::Time deltaTime);
            void coolantApplied(); // Subtracts coolant time from maximum time, calls updateWallGraphic().

        
        private:
            void updateGraphics(); // Changes size of wall graphic to reflect the remaining time left. Bigger = less time. 
            virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
    };

    namespace ComplicationFactories{
         bool generateFirewalls(std::list<Complication*> &complications, int jobInputs, int number, int maxLength, int minLength, float timeScale);
    };
}