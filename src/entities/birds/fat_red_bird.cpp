//
// Created by piotr on 5/9/23.
//

#include "include/entities/birds/fat_red_bird.hpp"

FatRedBird::FatRedBird(b2WorldId world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x, float coord_y){
    this->bird_textures = bird_textures;
    this->world = world;

    //General information
    this->type.main_type = TYPE_DATA::BIRD;
    this->type.sub_type = TYPE_DATA::FAT_RED_BIRD;

    this->sprite = sf::Sprite(*bird_textures[0]);
    this->sprite.setOrigin((float)(*bird_textures[0]).getSize().x/2, (float)(*bird_textures[0]).getSize().y/2);

    b2BodyDef bdef = b2DefaultBodyDef();
    bdef.userData = reinterpret_cast<void*>(this);
    bdef.type=b2_dynamicBody;
    bdef.position = b2Vec2(coord_x,coord_y);
    bdef.name = "Entity";

    b2Circle circle;
    circle.radius = 40/SCALE;

    m_body = b2CreateBody(world, &bdef);

    b2ShapeDef fixtureDef = b2DefaultShapeDef();

    fixtureDef.density = 2.f;
    fixtureDef.material.friction = 1;
    fixtureDef.material.restitution =  0.3f;
    fixtureDef.enableContactEvents = true;

    b2CreateCircleShape(m_body, &fixtureDef, &circle);
    b2Body_Disable(m_body);
}
