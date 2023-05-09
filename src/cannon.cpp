//
// Created by piotr on 5/6/23.
//

#include "cannon.hpp"

Cannon::Cannon(sf::Vector2f position, std::shared_ptr<EntityManager> manager){
    this->manager = std::move(manager);

    hull_texture.loadFromFile("textures/cannon/cannon_base.png");
    hull_texture.setSmooth(true);

    hull_sprite.setOrigin(hull_texture.getSize().x/2, hull_texture.getSize().y/2);
    hull_sprite.setPosition(position);
    hull_sprite.setTexture(hull_texture);

    cannon_texture.loadFromFile("textures/cannon/cannon.png");
    cannon_texture.setSmooth(true);

    cannon_sprite.setOrigin(cannon_texture.getSize().x/2-20, cannon_texture.getSize().y / 2);
    cannon_position = {position.x+40, position.y-hull_texture.getSize().y/2-cannon_texture.getSize().y/2+25};
    cannon_sprite.setPosition(cannon_position);
    cannon_sprite.setTexture(cannon_texture);

    this->bird_texture = std::make_shared<sf::Texture>();
    this->bird_texture->loadFromFile("textures/birds/bird_red.png");

}

void Cannon::update(sf::Vector2f mouse_position){
    angle = std::atan2(mouse_position.y - cannon_sprite.getPosition().y, mouse_position.x - cannon_sprite.getPosition().x);
    cannon_sprite.setRotation(angle * 57.29577);

    if(!this->manager->isBirdActive()){
        active = true;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && active){
        if(power < max_power){
            power += power_gain;
        }
    }
}

void Cannon::handleInput(const sf::Event e){
    if(e.type == sf::Event::MouseButtonReleased && active){
        if(e.mouseButton.button == sf::Mouse::Left){
            b2Vec2 velocity(power*std::cos(angle), power*std::sin(angle));
            sf::Vector2f position = {cannon_sprite.getPosition().x-20 + (cannon_texture.getSize().x / 2 + 20) * std::cos(angle), cannon_sprite.getPosition().y-20 + (cannon_texture.getSize().x / 2 + 20) * std::sin(angle)};

            std::unique_ptr<Bird> bird = std::make_unique<Bird>(this->manager->getWorld(), 0.2f, position.x/10, position.y/10, b2Vec2(0,0), *bird_texture);
            bird->applyForce(velocity);
            this->manager->pushEntity(std::move(bird));
            power = 0;

            // TODO Commented only for testing purposes, uncomment before release
            //active = false;
        }
    }
}

void Cannon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(cannon_sprite, states);
    target.draw(hull_sprite, states);
}
