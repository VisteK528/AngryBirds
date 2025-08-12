#include "include/entities/pigs/basic_pig/basic_pig.hpp"
#include <utility>

BasicPig::BasicPig(const b2WorldId world, const std::vector<std::shared_ptr<sf::Texture>>& textures, const float coord_x,
    const float coord_y): Pig(world, textures, coord_x, coord_y){
    this->type.sub_type = TYPE_DATA::BASIC_PIG;
    this->coliding = false;
    this->destroyed = false;

    this->health = 800;
    this->base_health = 800;

    this->score = 5000;

    density = 0.7f;
    friction = 0.5f;
    restitution = 0.5f;
    if(b2Shape_IsValid(shape_id_)) {
        b2Shape_SetDensity(shape_id_, density, true);
        b2Shape_SetFriction(shape_id_, friction);
        b2Shape_SetRestitution(shape_id_, restitution);
    }
}

void BasicPig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
