//
// Created by piotr on 5/4/23.
//

#include "entity.hpp"

#include <utility>

Entity::Entity() {
    this->coliding = false;
    this->destroyed = false;
}

Entity::Entity(std::shared_ptr<b2World> world, const sf::Texture& t){
    this->world = std::move(world);
    this->texture = std::make_unique<sf::Texture>(t);
    this->coliding = false;
    this->destroyed = false;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Entity::getDestroyed() const {
    return this->destroyed;
}

b2Body* Entity::getBody(){
    return this->m_body;
}