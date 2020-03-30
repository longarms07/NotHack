#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace RenderSystem {
    class RenderHandler : public Singleton<RenderHandler>, public sf::Drawable {
        private:
            std::list<const sf::Drawable*> drawableRegistrants;

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

        public:
            bool registerDrawable(const sf::Drawable*);
            bool unregisterDrawable(const sf::Drawable*);
    };
}