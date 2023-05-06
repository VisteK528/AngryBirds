#ifndef BIRD_HPP
#define BIRD_HPP

#include "entity.hpp"
#include <iostream>
#include <math.h>

class Bird: public Entity
{
private:
    sf::Texture t2;
    double health;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    void startCollision(b2Body* body_b) override;
    void endCollision(b2Body* body_b) override;
    void update() override;
    Bird(){};
    Bird(const std::shared_ptr<b2World>& world, float density, float coord_x, float coord_y, b2Vec2 velocity, const sf::Texture& t);
};

#endif