#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>
#include "../../box2d/include/box2d/b2_settings.h"
#include "entity.hpp"
#include <string>
#include <iostream>

class Bird: public Entity
{
private:
    sf::Texture t2;
    public:
        void startCollision() override;
        void endCollision() override;
        void update() override;
        Bird(){};
        Bird(const std::shared_ptr<b2World>& world, float density, float coord_x, float coord_y, b2Vec2 velocity, const sf::Texture& t);
};

#endif