#ifndef BIRD_HPP
#define BIRD_HPP

#include "include/entities/entity.hpp"
#include <iostream>
#include <math.h>

class Bird: public Entity
{
protected:
    std::vector<std::shared_ptr<sf::Texture>> bird_textures;
    bool action_available = true;
    bool countdown = false;
    sf::Clock despawn_clock;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    virtual void makeAction(){};
    void setActive(bool active);
    void setPosition(b2Vec2 position);
    void setRotation(float angle);
    void applyLinearVelocity(b2Vec2 velocity);
    void applyForce(b2Vec2 force);
    void startCollision(b2Body* body_b) override;
    void endCollision(b2Body* body_b) override;
    void update() override;
    Bird()=default;
    Bird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x=0, float coord_y=0);
};

#endif