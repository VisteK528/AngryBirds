#ifndef BIRD_HPP
#define BIRD_HPP

#include "../entity.hpp"
#include <iostream>
#include <math.h>

class Bird: public Entity
{
protected:
    b2Vec2 new_velocity;
    bool action_available = true;
    bool countdown = false;
    sf::Clock despawn_clock;

    void initVariables();
    virtual void loadTextures();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    virtual void makeAction(){};
    void setActive(bool active);
    void setPosition(b2Vec2 position);
    void applyLinearVelocity(b2Vec2 velocity);
    void applyForce(b2Vec2 force);
    void startCollision(b2Body* body_b) override;
    void endCollision(b2Body* body_b) override;
    void update() override;
    Bird(){};
    Bird(const std::shared_ptr<b2World>& world, float coord_x, float coord_y);
};

#endif