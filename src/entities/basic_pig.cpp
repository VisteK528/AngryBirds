#include "basic_pig.hpp"
#include <utility>

BasicPig::BasicPig(std::shared_ptr<b2World> world, float coord_x, float coord_y): Pig(std::move(world))
{
    this->type.sub_type = TYPE_DATA::BASIC_PIG;
    this->coliding = false;
    this->destroyed = false;

    this->health = 100;
    this->density = 0.7f;
    this->friction = 0.5f;
    this->restitution = 0.5f;

    this->t_intact.loadFromFile("textures/pigs/basic/basic_pig.png");
    this->t_damaged.loadFromFile("textures/pigs/basic/basic_pig.png");
    this->t_destroyed.loadFromFile("textures/pigs/basic/basic_pig.png");

    this->texture = std::make_unique<sf::Texture>(this->t_intact);
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(coord_x, coord_y);
    this->m_body = this->world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius=20/SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = this->density;
    fixtureDef.friction = this->friction;
    fixtureDef.restitution = this->restitution;
    m_body->CreateFixture(&fixtureDef);
}

void BasicPig::setTexture() {
    if (health > 66){
        this->texture = std::make_unique<sf::Texture>(this->t_intact);
    } else if (health > 33){
        this->texture = std::make_unique<sf::Texture>(this->t_damaged);
    } else {
        this->texture = std::make_unique<sf::Texture>(this->t_destroyed);
    }
    this->texture->setSmooth(true);
}

void BasicPig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}

void BasicPig::startCollision(b2Body* body_b) {
    // Calculate damage based on the velocity of the bird
    b2Vec2 vel = body_b->GetLinearVelocity();
    float damage = sqrt(vel.x*vel.x + vel.y*vel.y) * 0.5;

    // Reduce health
    this->health -= damage;

    if (this->health <= 0) {
        destroyed = true;
    }
}

void BasicPig::endCollision(b2Body* body_b) {
    this->setTexture();
    this->sprite.setTexture(*this->texture);
}