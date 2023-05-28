#include "include/entities/pigs/pig.hpp"
#include <utility>
#include <iostream>

Pig::Pig(std::shared_ptr<b2World> world): Entity(std::move(world))
{
    this->type.main_type = TYPE_DATA::PIG;
}

void Pig::update() {
    float angle = m_body->GetAngle();
    b2Vec2 pos = m_body->GetPosition();

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Pig::startCollision(b2Body* body_b) {
    // Obliczenie prędkości początkowych obu obiektów
    b2Vec2 v1_ini = this->m_body->GetLinearVelocity();
    b2Vec2 v2_ini = body_b->GetLinearVelocity();
    // Obliczenie prędkości ostatecznych obu obiektów
    float m1 = this->m_body->GetMass();
    float m2 = body_b->GetMass();

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
    this->m_body->ApplyLinearImpulse(-impulseVector, this->m_body->GetWorldCenter(), true);
    body_b->ApplyLinearImpulse(impulseVector, body_b->GetWorldCenter(), true);
    // Obliczenie obrażeń na podstawie masy obiektu body_b i prędkości względnej
    float damage = m2 * dv2.LengthSquared() / 2.0;
    // Redukcja zdrowia obiektu Pig


    // Próg wykrywania obrażeń
    if (damage < 50) {
        damage = 0;
    }
    else {
        std::cout << "Pig hit: " << damage << std::endl;
        this->health -= damage;
        if (this->health <= 0) {
        destroyed = true;
        }
    }
}

void Pig::endCollision(b2Body*) {
    this->setTexture();
    this->sprite.setTexture(*this->texture);
}

void Pig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Pig::setTexture() {
    if (health > (base_health*(2./3.))){
        this->texture = textures[INTACT];
    } else if (health > (base_health*(1./3.))){
        this->texture = textures[DAMAGED];
    } else {
        this->texture = textures[DESTROYED];
    }
    this->texture->setSmooth(true);
}
