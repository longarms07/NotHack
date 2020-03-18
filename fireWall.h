#include <SFML/Graphics.hpp>
#include <string>
#include "hackerWindow.h"

class FireWall : public sf::Drawable {

    public:

        FireWall(HackerWindow& parent, int targetChars, sf::Time maxTime, sf::Time coolTime); 
        void charEntered(); // Increments numEnteredChars, ends the firewall if target has been reached.
        /* Adds delta time to elapsed time, ends job in failure is greater than maximumTime.
           Calls updateWallGraphic(). */
        void update(sf::Time deltaTime); 
        void coolantApplied(); // Subtracts coolant time from maximum time, calls updateWallGraphic().


    private: 
        sf::Time elapsedTime; // The time the firewall has been active (the coolant subtracts time from it)
        sf::Time maximumTime; // The maximum time the firewall can be active before the mission is failed.
        sf::Time coolantTime; // The amount of time that applying a coolant removes from the firewall.
        int numTargetChars; // The number of characters that needs to be input before time runs out
        int numEnteredChars; // The number of characters that have been entered thus far
        sf::Vector2f maxAnchorPoint; // The highest possible anchor point, equal to the parent HackerWindow's anchorpoint
        sf::Vector2f minAnchorPoint; // The lowest possible anchor point, calculated from max and bounds
        sf::Vector2f maxBounds; // Maximum bounds of wallGraphic, equal to the bounds of HackerWindow. x is width, y is height.
        sf::RectangleShape wallGraphic; // The red, semi-transparent rectangle representing the firewall. 
        HackerWindow* parentHackerWindow;

        void EndFireWall(); // Notifies HackerWindow to set the firewall to null, deletes self. 
        void EndJob(); // Ends the current job in the parent
        void UpdateWallGraphic(); // Changes size of wall graphic to reflect the remaining time left. Bigger = less time. 
        virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const;

};