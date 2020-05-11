#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "progressBar.h"
#include "renderSystem.hpp"
#include "spriteAnimations.hpp"
#include <cstdlib>
 
/*****************************************************
 * This namespace consists of all classes related    *
 * to 'complications', obstacles that occur in jobs. *
 * ***************************************************/
namespace Complication {

    /*****************************************************
     * This structure is what is used by Jobs and the    *
     * JobSystem, to detect when a job is active and     *
     * Whether or not it was a success or failure.       *
     * ***************************************************/
    struct endData { 
        bool ended; // True if the job is ended, false if not
        bool defeated; // True if the player defeated the complication, false if the complication completed successfully
    };


    /*****************************************************
     * Complication:                                     *
     *      The Abstract Class that all complications    *
     *      Must be derived from.                        *
     * ***************************************************/
    class Complication {
        public:
            virtual ~Complication() { };

            virtual void startComplication() = 0; // Defines the behavior for starting a complication. 
            virtual void endComplication(bool defeated) = 0; // Defines behavior for ending a complication. "defeated" is true if the player defeated the complication.
            virtual void keyPressed() = 0; // Not event system
            virtual void update(sf::Time deltaTime) = 0; // Standard update function called by JobInstance


            endData getEndData();  // Getter method for current endData
            int getNumberKeysRequired(); // Getter method for the number of keys the complication expects to have
            double getPenaltyValue(); // Gets the monetary penalty of the job
            bool isActive(); // Returns whether or not the complication has been started

        protected:
            int numKeysReq; // Number of keyd the complication expects the hackerwindow to print before it is activated
            double penalty; // The monetary penalty of failure
            endData endingData; // The current endData of the complication
            bool active; // Whether or not the job has been started

    };


    /*****************************************************
     * Firewall:                                         *
     *     -A complication consisting of a wall of fire  *
     *      That must be defeated within a limited time  *
     *      To avoid the computer melting and failing a  *
     *      job. It can be slowed down by applying       *
     *      Coolant and defeated by entering enough      *
     *      key inputs during a job.                     *
     *    - A derived class of Drawable and Complication.*
     * Visuals:                                          *
     *     -A Wall of Fire covers a percentage of the    *
     *      Hackerwindow, growing larger as the firewall *
     *      Comes closer to making the player fail       *
     *      the job.                                     *
     *     -A progress bar under the HackerWindow shows  *
     *      The player's progress in defeating the       *
     *      Firewall.                                    *
     * WARNING:                                          *
     *      While multiple Firewalls may be instantiated,*
     *      only one should be active at a time to avoid *
     *      issues with Coolant and graphics.            *
     *      There is currently no check to enforce this. *
     * ***************************************************/
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

            // Offsets for drawing the Firewall visuals
            sf::Vector2f barOffset; 
            sf::Vector2f firewallOffset;
            
            // Layers for fire graphic
            SpriteAnimations::HorizontalSine* fireLayer1; 
            SpriteAnimations::HorizontalSine* fireLayer2;
            SpriteAnimations::HorizontalSine* fireLayer3;
            
            
            ProgressBar* progressBar; // The progress bar used to show the player's progress to breaking the firewall.

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


   /*****************************************************
    * This namespace consists factory methods used by   *
    * Jobs to get a dynamic list of complications.      *
    *****************************************************/
    namespace ComplicationFactories{
         // A Factory method that populates the referenced complication list with Firewalls.
         bool generateFirewalls(std::list<Complication*> &complications, int jobInputs, int number, int maxLength, int minLength, float timeScale);
    };
}