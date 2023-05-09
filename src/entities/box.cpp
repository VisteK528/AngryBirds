#include "box.hpp"

#include <utility>



Box::Box(std::shared_ptr<b2World> world): Entity(std::move(world))
{
    this->type.main_type = TYPE_DATA::BOX;
}

void Box::update() {
    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Box::startCollision(b2Body* body_b) {

    // Calculate damage based on the velocity of the bird

    float m1 = this->m_body->GetMass();
    float m2 = body_b->GetMass();

    b2Vec2 v1 = this->m_body->GetLinearVelocity();
    b2Vec2 v2 = body_b->GetLinearVelocity();

    float u_x = (m1*v1.x+m2*v2.x)/(m1+m2);
    float u_y = (m1*v1.y+m2*v2.y)/(m1+m2);
    b2Vec2 vel(u_x, u_y);

    float damage = m2*std::pow(sqrt(vel.x*vel.x + vel.y*vel.y), 2) * 0.5;
    std::cout<<"Damage: "<<damage<<std::endl;

    // Reduce health
    this->health -= damage;

    if(this->health <= 0){
        destroyed = true;
    }
}

void Box::endCollision(b2Body* body_b) {
    this->setTexture();
    this->sprite.setTexture(*this->texture);
}

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}