#include "include/entities/boxes/box.hpp"
#include <utility>


Box::Box(b2WorldId world): Entity(world)
{
    this->type.main_type = TYPE_DATA::BOX;
}

void Box::update() {
    float angle = b2Rot_GetAngle(b2Body_GetRotation(m_body));
    b2Vec2 pos = b2Body_GetPosition(m_body);

    sprite.setRotation(angle*DEG);
    sprite.setPosition(pos.x*SCALE+20, pos.y*SCALE+20);
}

void Box::startCollision(b2BodyId& body_b) {
    // Obliczenie prędkości początkowych obu obiektów
    b2Vec2 v1_ini = b2Body_GetLinearVelocity(m_body);
    b2Vec2 v2_ini = b2Body_GetLinearVelocity(body_b);
    // Obliczenie prędkości ostatecznych obu obiektów
    float m1 = b2Body_GetMass(m_body);
    float m2 = b2Body_GetMass(body_b);

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
    b2Body_ApplyLinearImpulse(m_body, -impulseVector, b2Body_GetWorldCenterOfMass(m_body), true);
    b2Body_ApplyLinearImpulse(body_b, impulseVector, b2Body_GetWorldCenterOfMass(m_body), true);


    // Obliczenie obrażeń na podstawie masy obiektu body_b i prędkości względnej
    float damage = m2 * b2LengthSquared(dv2) / 2.0;
    // Redukcja zdrowia obiektu Box


    // Próg wykrywania obrażeń
    if (damage < 50) {
        damage = 0;
    }
    else {
        std::cout << "Damage: " << damage << std::endl;
        this->health -= damage;
        if (this->health <= 0) {
            destroyed = true;
        }
    }


}


void Box::endCollision(b2BodyId& body_b) {
    this->setTexture();
    this->sprite.setTexture(*this->texture);
}

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Box::setTexture() {
    if (health > (base_health*(2./3.))){
        this->texture = textures[INTACT];
    } else if (health > (base_health*(1./3.))){
        this->texture = textures[DAMAGED];
    } else {
        this->texture = textures[DESTROYED];
    }
    this->texture->setSmooth(true);
}
