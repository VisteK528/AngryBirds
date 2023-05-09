#include "bird.hpp"



Bird::Bird(const std::shared_ptr<b2World>& world, float density, float coord_x, float coord_y, b2Vec2 velocity, const sf::Texture& t): Entity(world){
    //General information
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
        //std::cout<<despawn_clock.getElapsedTime().asSeconds()<<std::endl;
    }
}

void Bird::startCollision(b2Body* body_b){
    if(!countdown){
        despawn_clock.restart();
        countdown = true;
    }

    float m1 = this->m_body->GetMass();
    float m2 = body_b->GetMass();

    b2Vec2 v1 = this->m_body->GetLinearVelocity();
    b2Vec2 v2 = body_b->GetLinearVelocity();

    float u_x = (m1*v1.x+m2*v2.x)/(m1+m2);
    float u_y = (m1*v1.y+m2*v2.y)/(m1+m2);
    this->new_velocity = b2Vec2(u_x, u_y);

    uintptr_t dataB = body_b->GetUserData().pointer;
    if(dataB != 0){
        auto *i = reinterpret_cast<Entity *>(dataB);
        float damage = m1*std::pow(sqrt(new_velocity.x*new_velocity.x + new_velocity.y*new_velocity.y), 2) * 0.5;
        if(damage > i->getHealth()){
            float actual_kinetic_energy = damage-i->getHealth();
            float velocity = sqrt(2*actual_kinetic_energy/m1);
            float angle = this->m_body->GetAngle();
            this->new_velocity = b2Vec2(std::cos(angle)*velocity, std::sin(angle)*velocity);

        }
    }
}

void Bird::endCollision(b2Body* body_b){
    uintptr_t dataB = body_b->GetUserData().pointer;
    if(dataB != 0){
        auto *i = reinterpret_cast<Entity *>(dataB);
        if(i->getDestroyed()){
            this->m_body->SetLinearVelocity(new_velocity);
        }
    }
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(this->sprite, states);
}

void Bird::applyForce(b2Vec2 force) {
    this->m_body->ApplyForceToCenter(force, true);
}
