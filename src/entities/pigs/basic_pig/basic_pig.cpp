#include "include/entities/pigs/basic_pig/basic_pig.hpp"
#include <utility>

BasicPig::BasicPig(std::shared_ptr<b2World> world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y): Pig(std::move(world))
{
    this->type.sub_type = TYPE_DATA::BASIC_PIG;
    this->coliding = false;
    this->destroyed = false;

    this->health = 800;
    this->base_health = 800;

    this->score = 5000;

    this->density = 0.7f;
    this->friction = 0.5f;
    this->restitution = 0.5f;

    this->textures[INTACT] = textures[0];
    this->textures[DAMAGED] = textures[1];
    this->textures[DESTROYED] = textures[2];

    this->texture = this->textures[INTACT];
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

void BasicPig::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
