#pragma once
#include <SFML/Graphics.hpp>
#include <list>

/*************************************
 * namespace for the RenderHandler,
 * which is a subject for observers
 * that need to be drawn to subscribe
 * to at runtime
 **************************************/
namespace RenderSystem {
    class RenderHandler : public Singleton<RenderHandler>, public sf::Drawable {
        private:
            std::vector<std::list<const sf::Drawable*>*> drawableRegistrants;

            /*sf::Drawable*/
            void draw(sf::RenderTarget&, sf::RenderStates) const;

        public:
            bool registerDrawable(const sf::Drawable*, int layer=0); // Objects are drawn first in order of layer, and then by time subsribed,
                                                                     // with lower layers and older times being drawn first (on the bottom)
            bool unregisterDrawable(const sf::Drawable*);
    };
}