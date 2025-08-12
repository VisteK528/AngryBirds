#ifndef PIG_HPP
#define PIG_HPP

#include "aether/entities/entity.hpp"
#include <unordered_map>


class Pig: public Entity
{
    public:
        Pig()=default;
        ~Pig() override = default;
        Pig(b2WorldId world, const std::vector<std::shared_ptr<sf::Texture>>& textures, float coord_x, float coord_y);

        void update() override;
        void startCollision(b2BodyId& body_b) override;
        void endCollision(b2BodyId& body_b) override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    protected:
        typedef enum{INTACT, DAMAGED, DESTROYED} T_TYPE;
        std::unordered_map<T_TYPE, std::shared_ptr<sf::Texture>> textures;
        double base_health{};

        float density{};
        float friction{};
        float restitution{};

        b2ShapeId shape_id_;
        virtual void setTexture();
};

#endif