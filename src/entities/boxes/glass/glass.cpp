#include "glass.hpp"

#include <utility>

#include <iostream>

Glass::Glass(std::shared_ptr<b2World> world, float coord_x, float coord_y): Box(std::move(world)) {
    this->coliding = false;
    this->destroyed = false;
    this->type.sub_type = TYPE_DATA::GLASS;

    this->t_intact.loadFromFile("textures/boxes/glass/glass_1x1.png");
    this->t_damaged.loadFromFile("textures/boxes/glass/glass_1x1_damaged.png");
    this->t_destroyed.loadFromFile("textures/boxes/glass/glass_1x1_destroyed.png");

    this->texture = std::make_unique<sf::Texture>(this->t_intact);
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    this->health = 500;
    this->base_health = 500;

    this->density = 0.6f;
    this->friction = 0.1f;
    this->restitution = 0.1f;

    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(coord_x, coord_y);
    this->m_body = this->world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((this->sprite.getGlobalBounds().width/2)/SCALE, (this->sprite.getGlobalBounds().height/2)/SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = this->density;
    fixtureDef.friction = this->friction;
    fixtureDef.restitution = this->restitution;
    this->m_body->CreateFixture(&fixtureDef);
}

void Glass::setTexture() {
    if (health > base_health*(2./3.)){
        this->texture = std::make_unique<sf::Texture>(this->t_intact);
    } else if (health > base_health*(1./3.)){
        this->texture = std::make_unique<sf::Texture>(this->t_damaged);
    } else {
        this->texture = std::make_unique<sf::Texture>(this->t_destroyed);
    }
    this->texture->setSmooth(true);
}

void Glass::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}