//
// Created by piotr on 5/4/23.
//

#include "entity.hpp"

Entity::Entity() {
    this->name = "Jojo";
    this->coliding = false;
}

Entity::Entity(std::shared_ptr<b2World> world, const sf::Texture& t){
    this->world = world;
    this->texture = std::make_unique<sf::Texture>(t);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}