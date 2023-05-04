#ifndef BOX_HPP
#define BOX_HPP

#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "bird.hpp"
#include <memory>
#include <string>


class Box: public Entity
{
    public:
        void startCollision() override;
        void endCollision() override;
        void update() override;
        Box(){};
        Box(std::shared_ptr<b2World> world, float density, float coord_x, float coord_y, const sf::Texture& t);
};

#endif