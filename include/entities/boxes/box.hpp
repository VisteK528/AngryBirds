#ifndef BOX_HPP
#define BOX_HPP

#include "aether/entities/entity.hpp"
#include "include/entities/birds/bird.hpp"
#include <math.h>
#include <unordered_map>

class Box: public Entity
{
    public:
        void update() override;
        virtual void startCollision(b2BodyId& body_b) override;
        virtual void endCollision(b2BodyId& body_b) override;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        Box()=default;
        virtual ~Box(){};
        Box(b2WorldId world);

    protected:
        typedef enum{INTACT, DAMAGED, DESTROYED} T_TYPE;
        std::unordered_map<T_TYPE, std::shared_ptr<sf::Texture>> textures;
        double base_health;
        double health;

        float density;
        float friction;
        float restitution;

        virtual void setTexture();
};

#endif