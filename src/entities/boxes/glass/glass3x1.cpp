#include "include/entities/boxes/glass/glass3x1.hpp"
#include <utility>

Glass3x1::Glass3x1(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y, bool rotated): Box(std::move(world)) {
    this->coliding = false;
    this->destroyed = false;
    this->type.sub_type = TYPE_DATA::GLASS;

    this->textures[INTACT] = textures[0];
    this->textures[DAMAGED] = textures[1];
    this->textures[DESTROYED] = textures[2];

    this->texture = textures[INTACT];
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    this->health = 1500;
    this->base_health = 1500;

    this->score = 1500;

    this->density = 0.6f;
    this->friction = 0.1f;
    this->restitution = 0.1f;

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

void Glass3x1::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
