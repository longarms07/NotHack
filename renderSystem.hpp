#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace RenderSystem {
    class RenderHandler : public Singleton<RenderHandler>, public sf::Drawable {
        private:
            std::vector<std::list<const sf::Drawable*>*> drawableRegistrants;

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

        public:
            bool registerDrawable(const sf::Drawable*, int layer=0);
            bool unregisterDrawable(const sf::Drawable*);
    };
}