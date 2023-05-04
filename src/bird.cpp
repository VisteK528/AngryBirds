#include "bird.hpp"



Bird::Bird(std::shared_ptr<b2World> world, float density, float coord_x, float coord_y, b2Vec2 velocity, std::string name, const sf::Texture& t)
{
    this->sprite = sf::Sprite(t);
    this->sprite.setOrigin((float)t.getSize().x/2, (float)t.getSize().y/2);

    b2BodyDef bdef;

    data.number = 6;
    data.text = name;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(&data);

    std::unique_ptr<float> ptr = std::make_unique<float>(30);
    b2PolygonShape shape;
    shape.SetAsBox(20/(*ptr), 20/(*ptr));

    bdef.type=b2_dynamicBody;
    ////ball///
    bdef.position.Set(coord_x,coord_y);
    b2CircleShape circle;
    circle.m_radius=20/(*ptr);

    this->m_body = world->CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.9f;
    fdef.density = density;
    fdef.friction=0.9f;
    m_body->CreateFixture(&fdef);
    m_body->SetLinearVelocity(velocity);
}

void Bird::update() {
    const float SCALE = 30.0f;
    const float DEG = 57.29577f;

    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}