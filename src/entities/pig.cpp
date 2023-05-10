#include "pig.hpp"
#include <utility>

Pig::Pig(std::shared_ptr<b2World> world): Entity(std::move(world))
{
    this->type.main_type = TYPE_DATA::PIG;
}

void Pig::update() {
    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Pig::startCollision(b2Body* body_b) {

    // Calculate damage based on the velocity of the bird
    b2Vec2 vel = body_b->GetLinearVelocity();
    float damage = sqrt(vel.x*vel.x + vel.y*vel.y) * 0.5;

    // Reduce health
    this->health -= damage;

    if (this->health <= 0) {
        destroyed = true;
    }
}

void Pig::endCollision(b2Body*) {

}

void Pig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}