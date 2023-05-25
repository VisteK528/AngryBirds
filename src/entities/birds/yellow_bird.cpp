//
// Created by piotr on 5/9/23.
//

#include "include/entities/birds/yellow_bird.hpp"

#include <utility>

YellowBird::YellowBird(const std::shared_ptr<b2World>& world, std::vector<std::shared_ptr<sf::Texture>> bird_textures, float coord_x, float coord_y): Bird(world, bird_textures, coord_x, coord_y){
    this->sprite.setTexture(*bird_textures[0]);
    this->type.main_type = TYPE_DATA::BIRD;
    this->type.sub_type = TYPE_DATA::YELLOW_BIRD;
}

void YellowBird::makeAction(){
    if(action_available){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !dash_started){
            action_clock.restart();
            dash_started = true;
        }
        if(action_clock.getElapsedTime().asSeconds() < 3 && !dash_ended && dash_started){
            float angle = std::atan2(m_body->GetLinearVelocity().y, m_body->GetLinearVelocity().x);
            m_body->ApplyForceToCenter(b2Vec2(200000.f*std::cos(angle), 200000.f*std::sin(angle)), false);
            dash_ended = true;
        }
    }
};