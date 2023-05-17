#include "wood3x1.hpp"
#include <utility>

Wood3x1::Wood3x1(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y, bool rotated): Box(std::move(world)) {
    this->coliding = false;
    this->destroyed = false;
    this->type.sub_type = TYPE_DATA::WOOD;

    this->textures[INTACT] = textures[0];
    this->textures[DAMAGED] = textures[1];
    this->textures[DESTROYED] = textures[2];

    this->texture = textures[INTACT];
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    this->health = 3000;
    this->base_health = 3000;

    this->score = 3000;

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

void Wood3x1::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
