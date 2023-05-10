//
// Created by piotr on 5/9/23.
//

#include "yellow_bird.hpp"

YellowBird::YellowBird(const std::shared_ptr<b2World> &world, float coord_x, float coord_y): Bird(world, coord_x, coord_y){
    initVariables();
    this->sprite.setTexture(*this->texture);
    this->type.main_type = TYPE_DATA::BIRD;
    this->type.sub_type = TYPE_DATA::YELLOW_BIRD;
}

void YellowBird::loadTextures() {
    this->texture = std::make_unique<sf::Texture>();
    this->texture->loadFromFile("textures/birds/bird_yellow.png");
}

void YellowBird::makeAction(){
    if(action_available){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !dash_stared){
            action_clock.restart();
            dash_stared = true;
            this->m_body->GetFixtureList()->SetDensity(1.f);
        }
        if(action_clock.getElapsedTime().asSeconds() < 3 && !dash_ended && dash_stared){
            float angle = m_body->GetAngle();
            m_body->ApplyForceToCenter(b2Vec2(100000*std::cos(angle), 100000*std::sin(angle)), false);
            dash_ended = true;
        }
    }
};