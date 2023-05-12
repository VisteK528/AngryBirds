#include "bird.hpp"



Bird::Bird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x, float coord_y): Entity(world){
    this->bird_textures = bird_textures;

    //General information
    this->type.main_type = TYPE_DATA::BIRD;
    this->sprite = sf::Sprite(*bird_textures[0]);
    this->sprite.setOrigin((float)(*bird_textures[0]).getSize().x/2, (float)(*bird_textures[0]).getSize().y/2);

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
    fdef.density = 0.5f;
    fdef.friction=1;
    m_body->CreateFixture(&fdef);
    m_body->SetEnabled(false);
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
    }
}

void Bird::startCollision(b2Body*) {
    this->action_available = false;
}

void Bird::endCollision(b2Body* body_b){

    // Obliczenie prędkości początkowych obu obiektów
    b2Vec2 v1_ini = this->m_body->GetLinearVelocity();
    b2Vec2 v2_ini = body_b->GetLinearVelocity();
    // Obliczenie prędkości ostatecznych obu obiektów
    float m1 = this->m_body->GetMass();
    float m2 = body_b->GetMass();

    this->action_available = false;

    // Jeśli masa obiektu body_b jest równa 0,
    // to przyjmuje się, że jest on ścianą
    // i nadajemy mu parametry obiektu pierwszego
    if (m2 == 0) {
        m2 = m1;
        v2_ini = v1_ini;
    }

    b2Vec2 v1 = this->m_body->GetLinearVelocity();
    b2Vec2 v2 = body_b->GetLinearVelocity();
    b2Vec2 vel((m1*v1.x+m2*v2.x)/(m1+m2), (m1*v1.y+m2*v2.y)/(m1+m2));
    // Obliczenie wektorów zmiany prędkości dla obu obiektów
    b2Vec2 dv1 = vel - v1_ini;
    b2Vec2 dv2 = vel - v2_ini;
    // Obliczenie kąta zderzenia
    float angle = 0;
    if (vel.LengthSquared() > 0) {
        angle = atan2f(vel.y, vel.x);
    }
    // Obliczenie siły uderzenia
    float force = dv1.Length() * m1 + dv2.Length() * m2;
    force *= 2; // korekta
    // Obliczenie impulsu dla obu obiektów
    float impulse = force / (m1 + m2);
    b2Vec2 impulseVector(impulse * cos(angle), impulse * sin(angle));

    // Zastosowanie impulsu dla obu obiektów

    uintptr_t dataB = body_b->GetUserData().pointer;
    if(dataB != 0){
        auto *i = reinterpret_cast<Entity *>(dataB);
        if(i->getDestroyed()){
            this->m_body->ApplyLinearImpulse(impulseVector, this->m_body->GetWorldCenter(), true);
        }
    }
    else {
        // Zastosowanie impulsu dla obu obiektów
        body_b->ApplyLinearImpulse(impulseVector, body_b->GetWorldCenter(), true);
        this->m_body->ApplyLinearImpulse(-impulseVector, this->m_body->GetWorldCenter(), true);
    }
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(this->sprite, states);
}

void Bird::applyForce(b2Vec2 force) {
    this->m_body->ApplyForceToCenter(force, true);
}

void Bird::applyLinearVelocity(b2Vec2 velocity){
    this->m_body->SetLinearVelocity(velocity);
}

void Bird::setPosition(b2Vec2 position) {
    this->m_body->SetTransform(position, this->m_body->GetAngle());
}

void Bird::setActive(bool active) {
    this->m_body->SetEnabled(active);
}
