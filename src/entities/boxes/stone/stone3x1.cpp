#include "stone3x1.hpp"
#include <utility>

Stone3x1::Stone3x1(std::shared_ptr<b2World> world, float coord_x, float coord_y, bool rotated): Box(std::move(world)) {
    this->coliding = false;
    this->destroyed = false;
    this->type.sub_type = TYPE_DATA::STONE;

    this->t_intact.loadFromFile("textures/boxes/stone/stone_3x1.png");
    this->t_damaged.loadFromFile("textures/boxes/stone/stone_3x1_damaged.png");
    this->t_destroyed.loadFromFile("textures/boxes/stone/stone_3x1_destroyed.png");

    this->texture = std::make_unique<sf::Texture>(this->t_intact);
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    this->health = 9000;
    this->base_health = 9000;

    this->density = 0.7f;
    this->friction = 0.5f;
    this->restitution = 0.5f;

    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(coord_x, coord_y);

    // Ustawianie obrotu na podstawie parametru rotated
    if (rotated){
        bodyDef.angle = 90 / DEG;
    }

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

void Stone3x1::setTexture() {
    if (health > (base_health*(2./3.))){
        this->texture = std::make_unique<sf::Texture>(this->t_intact);
    } else if (health > (base_health*(1./3.))){
        this->texture = std::make_unique<sf::Texture>(this->t_damaged);
    } else {
        this->texture = std::make_unique<sf::Texture>(this->t_destroyed);
    }
    this->texture->setSmooth(true);
}

void Stone3x1::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
