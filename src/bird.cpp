#include "bird.hpp"



Bird::Bird(b2World *world, float density, float coord_x, float coord_y, b2Vec2 velocity, std::string name)
{
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

    b2Body *b = world->CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.9f;
    fdef.density = density;
    fdef.friction=0.9f;
    b->CreateFixture(&fdef);
    b->SetLinearVelocity(velocity);

}