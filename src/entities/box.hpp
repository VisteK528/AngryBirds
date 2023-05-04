#ifndef BOX_HPP
#define BOX_HPP

#include <SFML/Graphics.hpp>
#include "../../box2d/include/box2d/box2d.h"
#include "../../box2d/include/box2d/b2_settings.h"
#include "bird.hpp"
#include <memory>
#include <string>


class Box: public sf::Drawable
{
    private:
        b2Body* m_body;
        sf::Sprite sprite;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    public:
        void update();
        Box(){};
        Box(std::shared_ptr<b2World> world, float density, float coord_x, float coord_y, const sf::Texture& t);
};

#endif