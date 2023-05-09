#include "wood.hpp"
#include <utility>

Wood::Wood(std::shared_ptr<b2World> world, float coord_x, float coord_y): Box(std::move(world)) {
    this->coliding = false;
    this->destroyed = false;
    this->type.sub_type = TYPE_DATA::WOOD;

    this->t_intact.loadFromFile("textures/boxes/wood/wood_1x1.png");
    this->t_damaged.loadFromFile("textures/boxes/wood/wood_1x1_damaged.png");
    this->t_destroyed.loadFromFile("textures/boxes/wood/wood_1x1_destroyed.png");

    this->texture = std::make_unique<sf::Texture>(this->t_intact);
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    this->health = 100;

    this->density = 0.7f;
    this->friction = 0.5f;
    this->restitution = 0.5f;

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

void Wood::setTexture() {
    if (health > 66){
        this->texture = std::make_unique<sf::Texture>(this->t_intact);
    } else if (health > 33){
        this->texture = std::make_unique<sf::Texture>(this->t_damaged);
    } else {
        this->texture = std::make_unique<sf::Texture>(this->t_destroyed);
    }
    this->texture->setSmooth(true);
}

void Wood::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    // this->setTexture();
    // this->sprite.setTexture(*this->texture);

    target.draw(this->sprite, states);
}
