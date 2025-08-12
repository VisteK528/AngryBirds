#include "include/entities/boxes/wood/wood.hpp"
#include <utility>

Wood::Wood(b2WorldId world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y): Box(world)
{
    this->coliding = false;
    this->destroyed = false;
    this->type.sub_type = TYPE_DATA::WOOD;

    this->textures[INTACT] = textures[0];
    this->textures[DAMAGED] = textures[1];
    this->textures[DESTROYED] = textures[2];

    this->texture = textures[INTACT];
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

    this->health = 1000;
    this->base_health = 1000;

    this->score = 1000;

    this->density = 0.7f;
    this->friction = 0.5f;
    this->restitution = 0.5f;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.userData = reinterpret_cast<void*>(this);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(coord_x, coord_y);
    this->m_body = b2CreateBody(world, &bodyDef);

    b2Polygon dynamiBox = b2MakeBox((this->sprite.getGlobalBounds().width/2)/SCALE, (this->sprite.getGlobalBounds().height/2)/SCALE);

    b2ShapeDef fixtureDef = b2DefaultShapeDef();
    fixtureDef.enableContactEvents = true;
    fixtureDef.density = this->density;
    fixtureDef.material.friction = this->friction;
    fixtureDef.material.restitution = this->restitution;
    b2CreatePolygonShape(m_body, &fixtureDef, &dynamiBox);
}

void Wood::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
