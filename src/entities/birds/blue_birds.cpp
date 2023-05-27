//
// Created by piotr on 5/9/23.
//

/*
#include "blue_birds.hpp"


BlueBirds::BlueBirds(const std::shared_ptr<b2World>& world, float coord_x, float coord_y){
    initVariables();

    //General information
    this->type.main_type = TYPE_DATA::BIRD;
    sprites.push_back(sf::Sprite(*this->texture));
    sprites[0].setOrigin((float)(*this->texture).getSize().x/2, (float)(*this->texture).getSize().y/2);

    addBody(coord_x, coord_y);
}

void BlueBirds::addBody(float coord_x, float coord_y) {
    b2BodyDef bdef;
    bdef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2PolygonShape shape;
    shape.SetAsBox(20/SCALE, 20/SCALE);

    bdef.type=b2_dynamicBody;
    ////ball///
    bdef.position.Set(coord_x,coord_y);
    b2CircleShape circle;
    circle.m_radius=20/SCALE;

    bodies.push_back(m_body = world->CreateBody(&bdef));
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.5f;
    fdef.density = 0.2f;
    fdef.friction=1;
    bodies[bodies.size()-1]->CreateFixture(&fdef);
}

void BlueBirds::update() {
    m_body->GetFixtureList()
}

void BlueBirds::makeAction(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !split_started){
        float coord_x, coord_y;
        coord_x = bodies[0]->GetPosition().x;
        coord_y = bodies[0]->GetPosition().y;
        addBody(coord_x, coord_y-25);
        addBody(coord_x, coord_y+25);
        split_started = true;
    }
};

void BlueBirds::initTextures() {
    this->texture = std::make_unique<sf::Texture>();
    this->texture->loadFromFile("textures/birds/bird_blue.png");
}

void BlueBirds::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    for(const sf::Sprite& sprite: sprites){
        target.draw(sprite, states);
    }
}*/
