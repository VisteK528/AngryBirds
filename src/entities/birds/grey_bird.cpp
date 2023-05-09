//
// Created by piotr on 5/9/23.
//

#include "grey_bird.hpp"

GreyBird::GreyBird(const std::shared_ptr<b2World> &world, float coord_x, float coord_y): Bird(world, coord_x, coord_y){
    initVariables();
    this->sprite.setTexture(*this->texture);
    this->type.main_type = TYPE_DATA::BIRD;
    this->type.sub_type = TYPE_DATA::GREY_BIRD;
}

void GreyBird::loadTextures() {
    this->texture = std::make_unique<sf::Texture>();
    this->texture->loadFromFile("textures/birds/bird_blue.png");
}

void GreyBird::makeAction(){
    if(action_available){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !dash_stared){
            action_clock.restart();
            this->m_body->SetLinearVelocity(b2Vec2(0,0));
            dash_stared = true;
        }
        if(action_clock.getElapsedTime().asSeconds() < 3 && !dash_ended && dash_stared){
            m_body->ApplyForceToCenter(b2Vec2(0, 50000), false);
            dash_ended = true;
        }
    }
};