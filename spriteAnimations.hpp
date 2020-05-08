#pragma once
#include <SFML/Graphics.hpp>

namespace SpriteAnimations {
    class HorizontalSine : public sf::Drawable {
        private:
            float height;
            float period;
            sf::Sprite* originalSprite;

            double currentTime;

        public:
            HorizontalSine(sf::Sprite*, float height, float period, float startTime=0);
            ~HorizontalSine();

            void update(sf::Time);
            void draw(sf::RenderTarget&, sf::RenderStates) const;

            sf::Sprite& getSprite();
    };
}