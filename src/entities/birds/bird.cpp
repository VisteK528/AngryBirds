#include "bird.hpp"



Bird::Bird(const std::shared_ptr<b2World>& world, float coord_x, float coord_y): Entity(world){
    initVariables();

    //General information
    this->type.main_type = TYPE_DATA::BIRD;
    this->sprite = sf::Sprite(*this->texture);
    this->sprite.setOrigin((float)(*this->texture).getSize().x/2, (float)(*this->texture).getSize().y/2);

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
    fdef.density = 0.2f;
    fdef.friction=1;
    m_body->CreateFixture(&fdef);
}

void Bird::update() {
    makeAction();
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

void Bird::initVariables() {
    loadTextures();
}

void Bird::loadTextures() {
    this->texture = std::make_unique<sf::Texture>();
    this->texture->loadFromFile("textures/birds/bird_red.png");
}
