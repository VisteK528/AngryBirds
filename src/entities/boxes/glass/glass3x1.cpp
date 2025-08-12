#include "include/entities/boxes/glass/glass3x1.hpp"
#include <utility>

Glass3x1::Glass3x1(b2WorldId world, std::vector<std::shared_ptr<sf::Texture>> textures, float coord_x, float coord_y, bool rotated): Box(world) {
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

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.userData = reinterpret_cast<void*>(this);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(coord_x, coord_y);

    // Ustawianie obrotu na podstawie parametru rotated
    if (rotated){
        bodyDef.rotation = b2MakeRot(90 / DEG);
    }

    m_body = b2CreateBody(world, &bodyDef);

    b2Polygon dynamiBox = b2MakeBox((this->sprite.getGlobalBounds().width/2)/SCALE, (this->sprite.getGlobalBounds().height/2)/SCALE);

    b2ShapeDef fixtureDef = b2DefaultShapeDef();

    fixtureDef.density = this->density;
    fixtureDef.material.friction = this->friction;
    fixtureDef.material.restitution = this->restitution;
    b2CreatePolygonShape(m_body, &fixtureDef, &dynamiBox);
}

void Glass3x1::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}
