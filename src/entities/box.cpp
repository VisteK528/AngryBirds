#include "box.hpp"

#include <utility>



Box::Box(std::shared_ptr<b2World> world, float coord_x, float coord_y): Entity(std::move(world))
{
    this->type = BOX;
}

void Box::update() {
    const float SCALE = 10.0f;
    const float DEG = 57.29577f;

    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Box::startCollision() {

}

void Box::endCollision() {

}