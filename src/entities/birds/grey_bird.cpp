//
// Created by piotr on 5/9/23.
//

#include "include/entities/birds/grey_bird.hpp"

#include <utility>

GreyBird::GreyBird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x, float coord_y): Bird(world, bird_textures, coord_x, coord_y){
    this->sprite.setTexture(*bird_textures[0]);
    this->type.main_type = TYPE_DATA::BIRD;
    this->type.sub_type = TYPE_DATA::GREY_BIRD;
}

void GreyBird::makeAction(){
    if(action_available){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !dash_stared){
            action_clock.restart();
            this->m_body->SetLinearVelocity(b2Vec2(0,0));
            dash_stared = true;
        }
        if(action_clock.getElapsedTime().asSeconds() < 3 && !dash_ended && dash_stared){
            m_body->ApplyForceToCenter(b2Vec2(0, 500000), false);
            dash_ended = true;
        }
    }
};