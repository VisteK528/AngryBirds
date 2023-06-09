//
// Created by piotr on 5/4/23.
//

#include "include/entities/entity.hpp"

#include <utility>

Entity::Entity() {
    this->coliding = false;
    this->destroyed = false;
}

Entity::Entity(std::shared_ptr<b2World> world){
    this->world = std::move(world);
    this->coliding = false;
    this->destroyed = false;
}

bool Entity::getDestroyed() const {
    return this->destroyed;
}

b2Body* Entity::getBody(){
    return this->m_body;
}


void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

const TYPE_DATA &Entity::getType() const {
    return type;
}

double Entity::getHealth() const {
    return health;
}

int Entity::getScore() {
    return score;
}

void Entity::setDestroyed() {
    this->destroyed = true;
}