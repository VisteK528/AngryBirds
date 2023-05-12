#ifndef PIG_HPP
#define PIG_HPP

#include "../entity.hpp"
#include "../birds/bird.hpp"
#include <math.h>

class Pig: public Entity
{
    public:
        void update() override;
        virtual void startCollision(b2Body* body_b) override;
        virtual void endCollision(b2Body* body_b) override;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        Pig(){};
        virtual ~Pig(){};
        Pig(std::shared_ptr<b2World> world);

    protected:
        sf::Texture t_intact;
        sf::Texture t_damaged;
        sf::Texture t_destroyed;
        double base_health;
        double health;

        float density;
        float friction;
        float restitution;

        virtual void setTexture()=0;
};

#endif