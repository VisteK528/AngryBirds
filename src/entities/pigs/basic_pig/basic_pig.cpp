#include "basic_pig.hpp"
#include <utility>

BasicPig::BasicPig(std::shared_ptr<b2World> world, float coord_x, float coord_y): Pig(std::move(world))
{
    this->type.sub_type = TYPE_DATA::BASIC_PIG;
    this->coliding = false;
    this->destroyed = false;

    this->health = 2000;
    this->base_health = 2000;
    this->density = 0.7f;
    this->friction = 0.5f;
    this->restitution = 0.5f;

    this->t_intact.loadFromFile("textures/pigs/basic/basic_pig.png");
    this->t_damaged.loadFromFile("textures/pigs/basic/basic_pig_damaged.png");
    this->t_destroyed.loadFromFile("textures/pigs/basic/basic_pig_destroyed.png");

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
    if (health > (base_health*(2./3.))){
        this->texture = std::make_unique<sf::Texture>(this->t_intact);
    } else if (health > (base_health*(1./3.))){
        this->texture = std::make_unique<sf::Texture>(this->t_damaged);
    } else {
        this->texture = std::make_unique<sf::Texture>(this->t_destroyed);
    }
    this->texture->setSmooth(true);
}

void BasicPig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
