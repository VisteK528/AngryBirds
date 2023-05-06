#include "box.hpp"

#include <utility>



Box::Box(std::shared_ptr<b2World> world): Entity(std::move(world))
{
    this->type.main_type = TYPE_DATA::BOX;
}

void Box::update() {
    const float SCALE = 10.0f;
    const float DEG = 57.29577f;

    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Box::startCollision(b2Body* body_b) {

}

void Box::endCollision(b2Body* body_b) {

}