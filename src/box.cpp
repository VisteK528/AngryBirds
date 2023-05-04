#include "box.hpp"



Box::Box(std::shared_ptr<b2World> world, float density, float coord_x, float coord_y, std::string name, const sf::Texture& t)
{
    this->sprite = sf::Sprite(t);
    this->sprite.setOrigin((float)t.getSize().x/2, (float)t.getSize().y/2);

    data.number = 10;
    data.text = name;

    b2BodyDef bdef;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(&data);
    bdef.type=b2_dynamicBody;
    bdef.position.Set(coord_x,coord_y);
    this->m_body = world->CreateBody(&bdef);

    std::unique_ptr<float> ptr = std::make_unique<float>(10);

    b2PolygonShape shape;
    shape.SetAsBox(20/(*ptr), 20/(*ptr));

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

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}