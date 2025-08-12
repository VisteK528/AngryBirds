#include "include/entities/birds/bird.hpp"
#include "box2d/box2d.h"


Bird::Bird(b2WorldId world,
           std::vector<std::shared_ptr<sf::Texture>> bird_textures,
           float coord_x, float coord_y)
: Entity(world)
{
    this->bird_textures = std::move(bird_textures);

    score = 10000;
    type.main_type = TYPE_DATA::BIRD;

    sprite = sf::Sprite(*this->bird_textures.at(0));
    const auto sz = this->bird_textures.at(0)->getSize();
    sprite.setOrigin(static_cast<float>(sz.x) * 0.5f,
                     static_cast<float>(sz.y) * 0.5f);

    // --- Body (v3) ---
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {coord_x, coord_y};
    bodyDef.userData = this; // ok: void* in v3
    bodyDef.name = "Entity";

    m_body = b2CreateBody(world, &bodyDef); // m_body: b2BodyId

    // --- Shape/Material (v3) ---
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 3.0f;
    shapeDef.material.friction = 1.0f;
    shapeDef.material.restitution = 0.2f;
    shapeDef.enableContactEvents = true;

    // Circle (local to body)
    b2Circle circle;
    circle.center = {0.0f, 0.0f};
    circle.radius = 20.0f / SCALE;

    b2CreateCircleShape(m_body, &shapeDef, &circle);

    // If you need it disabled initially (v3 keeps Enable/Disable helpers)
    b2Body_Disable(m_body);
}

void Bird::update() {
    makeAction();
    float angle = b2Rot_GetAngle(b2Body_GetRotation(m_body));
    b2Vec2 pos = b2Body_GetPosition(m_body);

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);

    if(countdown){
        if(despawn_clock.getElapsedTime().asSeconds() >= 10){
            destroyed = true;
        }
    }
}

void Bird::startCollision(b2BodyId& body_b) {
    if(!countdown){
        despawn_clock.restart();
        countdown = true;
    }
    this->action_available = false;
}

void Bird::endCollision(b2BodyId& body_b){

    // Obliczenie prędkości początkowych obu obiektów
    b2Vec2 v1_ini = b2Body_GetLinearVelocity(m_body);
    b2Vec2 v2_ini = b2Body_GetLinearVelocity(body_b);

    // Obliczenie prędkości ostatecznych obu obiektów
    float m1 = b2Body_GetMass(m_body);
    float m2 = b2Body_GetMass(body_b);

    this->action_available = false;

    // Jeśli masa obiektu body_b jest równa 0,
    // to przyjmuje się, że jest on ścianą
    // i nadajemy mu parametry obiektu pierwszego
    if (m2 == 0) {
        m2 = m1;
        v2_ini = v1_ini;
    }

    b2Vec2 v1 = b2Body_GetLinearVelocity(m_body);
    b2Vec2 v2 = b2Body_GetLinearVelocity(body_b);
    b2Vec2 vel((m1*v1.x+m2*v2.x)/(m1+m2), (m1*v1.y+m2*v2.y)/(m1+m2));
    // Obliczenie wektorów zmiany prędkości dla obu obiektów
    b2Vec2 dv1 = vel - v1_ini;
    b2Vec2 dv2 = vel - v2_ini;
    // Obliczenie kąta zderzenia
    float angle = 0;
    if (b2LengthSquared(vel) > 0) {
        angle = atan2f(vel.y, vel.x);
    }
    // Obliczenie siły uderzenia
    float force = b2Length(dv1) * m1 + b2Length(dv2) * m2;
    force *= 2; // korekta
    // Obliczenie impulsu dla obu obiektów
    float impulse = force / (m1 + m2);
    b2Vec2 impulseVector(impulse * cos(angle), impulse * sin(angle));

    // Zastosowanie impulsu dla obu obiektów

    void* dataB = b2Body_GetUserData(body_b);
    if(dataB != 0){
        auto *i = reinterpret_cast<Entity *>(dataB);
        if(i->getDestroyed()){
            b2Body_ApplyLinearImpulse(m_body, impulseVector, b2Body_GetWorldCenterOfMass(m_body), true);
        }
    }
    else {
        // Zastosowanie impulsu dla obu obiektów
        b2Body_ApplyLinearImpulse(body_b, impulseVector, b2Body_GetWorldCenterOfMass(m_body), true);
        b2Body_ApplyLinearImpulse(m_body, -impulseVector, b2Body_GetWorldCenterOfMass(m_body), true);
    }
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(this->sprite, states);
}

void Bird::applyForce(b2Vec2 force) {
    b2Body_ApplyForceToCenter(m_body, force, true);
}

void Bird::applyLinearVelocity(b2Vec2 velocity){
    b2Body_SetLinearVelocity(m_body, velocity);
}

void Bird::setPosition(b2Vec2 position) {
    b2Body_SetTransform(m_body, position, b2Body_GetRotation(m_body));

    float angle = b2Rot_GetAngle(b2Body_GetRotation(m_body));
    b2Vec2 pos = b2Body_GetPosition(m_body);
    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Bird::setActive() {
    b2Body_Enable(m_body);
}

void Bird::setRotation(float angle) {
    sprite.setRotation(angle*DEG);
}
