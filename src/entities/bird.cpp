#include "bird.hpp"



Bird::Bird(const std::shared_ptr<b2World>& world, float density, float coord_x, float coord_y, b2Vec2 velocity, const sf::Texture& t): Entity(world){
    //General information
    this->health = 3000;
    this->type.main_type = TYPE_DATA::BIRD;

    this->sprite = sf::Sprite(t);
    this->sprite.setOrigin((float)t.getSize().x/2, (float)t.getSize().y/2);

    b2BodyDef bdef;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2PolygonShape shape;
    shape.SetAsBox(20/SCALE, 20/SCALE);

    bdef.type=b2_dynamicBody;
    ////ball///
    bdef.position.Set(coord_x,coord_y);
    b2CircleShape circle;
    circle.m_radius=20/SCALE;

    this->m_body = world->CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.5f;
    fdef.density = density;
    fdef.friction=1;
    m_body->CreateFixture(&fdef);
    m_body->SetLinearVelocity(velocity);

    t2.loadFromFile("textures/boxes/wood/wood_1x1.png");
}

void Bird::update() {
    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);

    if(countdown){
        if(despawn_clock.getElapsedTime().asSeconds() >= 10){
            destroyed = true;
        }
        std::cout<<despawn_clock.getElapsedTime().asSeconds()<<std::endl;
    }
}

void Bird::startCollision(b2Body* body_b){
    if(!countdown){
        despawn_clock.restart();
        countdown = true;
    }
}

void Bird::endCollision(b2Body* body_b){

}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(this->sprite, states);
}