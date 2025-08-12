#include "include/entities/pigs/armored_pig/armored_pig.hpp"

ArmoredPig::ArmoredPig(const b2WorldId world, const std::vector<std::shared_ptr<sf::Texture>>& textures,
    const float coord_x, const float coord_y): Pig(world, textures, coord_x, coord_y){
    this->type.sub_type = TYPE_DATA::ARMORED_PIG;
    this->coliding = false;
    this->destroyed = false;

    this->health = 2000;
    this->base_health = 2000;

    this->score = 7000;

    density = 0.9f;
    friction = 0.3f;
    restitution = 0.3f;
    if(b2Shape_IsValid(shape_id_)) {
        b2Shape_SetDensity(shape_id_, density, true);
        b2Shape_SetFriction(shape_id_, friction);
        b2Shape_SetRestitution(shape_id_, restitution);
    }
}

void ArmoredPig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
