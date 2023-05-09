#ifndef BOX_HPP
#define BOX_HPP

#include "entity.hpp"
#include "birds/bird.hpp"
#include <math.h>


class Box: public Entity
{
    public:
        void update() override;
        void startCollision() override;
        void endCollision() override;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)=0;
        Box(){};
        virtual ~Box(){};
        Box(std::shared_ptr<b2World> world);

    protected:
        sf::Texture t_intact;
        sf::Texture t_damaged;
        sf::Texture t_destroyed;
        double health;

        float density;
        float friction;
        float restitution;
};

#endif