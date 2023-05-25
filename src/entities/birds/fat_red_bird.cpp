//
// Created by piotr on 5/9/23.
//

#include "include/entities/birds/fat_red_bird.hpp"

FatRedBird::FatRedBird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x, float coord_y){
    this->bird_textures = bird_textures;
    this->world = world;

    //General information
    this->type.main_type = TYPE_DATA::BIRD;
    this->type.sub_type = TYPE_DATA::FAT_RED_BIRD;

    this->sprite = sf::Sprite(*bird_textures[0]);
    this->sprite.setOrigin((float)(*bird_textures[0]).getSize().x/2, (float)(*bird_textures[0]).getSize().y/2);

    b2BodyDef bdef;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2PolygonShape shape;
    shape.SetAsBox(40/SCALE, 40/SCALE);

    bdef.type=b2_dynamicBody;
    ////ball///
    bdef.position.Set(coord_x,coord_y);
    b2CircleShape circle;
    circle.m_radius=40/SCALE;

    this->m_body = world->CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.3f;
    fdef.density = 1.f;
    fdef.friction=1;
    m_body->CreateFixture(&fdef);
    m_body->SetEnabled(false);
}
