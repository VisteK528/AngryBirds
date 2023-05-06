#include "box.hpp"



Box::Box(std::shared_ptr<b2World> world, float density, float coord_x, float coord_y, const sf::Texture& t): Entity(world, t)
{
    //General information
    this->type = BIRD;

    this->sprite = sf::Sprite(*this->texture);
    this->sprite.setOrigin((float)t.getSize().x/2, (float)t.getSize().y/2);

    b2BodyDef bdef;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bdef.type=b2_dynamicBody;
    bdef.position.Set(coord_x,coord_y);
    this->m_body = world->CreateBody(&bdef);

    float ptr = 10;

    b2PolygonShape shape;
    shape.SetAsBox(20/ptr, 20/ptr);

    b2FixtureDef fdef;
    fdef.shape = &shape;
    fdef.restitution = 0.1f;
    fdef.density = density;
    fdef.friction=0.9f;
    m_body->CreateFixture(&fdef);
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