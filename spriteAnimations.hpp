#pragma once
#include <SFML/Graphics.hpp>

/**********************************
 * Namespace for sprite animations
 **********************************/
namespace SpriteAnimations {
    /******************************
     * HorizontalSinge:
     *  - A class that moves its sprite
     *    back and forth
     *  - Used for firewall layers
     ******************************/
    class HorizontalSine : public sf::Drawable {
        private:
            float height; // Amplitude of the sine
            float period; // Period of sine
            sf::Sprite* originalSprite; // Sprite to draw

            double currentTime; // Time into the animation

        public:
            HorizontalSine(sf::Sprite*, float height, float period, float startTime=0);
            ~HorizontalSine();

            void update(sf::Time);
            void draw(sf::RenderTarget&, sf::RenderStates) const;

            sf::Sprite& getSprite();
    };
}