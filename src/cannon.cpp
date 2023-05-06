//
// Created by piotr on 5/6/23.
//

#include "cannon.hpp"

Cannon::Cannon(sf::Vector2f position, std::shared_ptr<EntityManager> manager){
    this->manager = std::move(manager);
    this->world = std::move(world);

    sf::Image image;
    image.create(200, 50, sf::Color(255, 0, 0, 255));
    // texture.loadFromImage(image);
    texture.loadFromFile("textures/cannon/cannon.png");
    texture.setSmooth(true);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(position);
    sprite.setTexture(texture);

    this->bird_texture = std::make_shared<sf::Texture>();
    this->bird_texture->loadFromFile("textures/birds/bird_red.png");

}

void Cannon::update(sf::Vector2i mouse_position){
    angle = std::atan2(mouse_position.y-sprite.getPosition().y, mouse_position.x-sprite.getPosition().x);
    sprite.setRotation(angle*57.29577);
}

void Cannon::handleInput(const sf::Event e){
    if(e.type == sf::Event::MouseButtonReleased){
        if(e.mouseButton.button == sf::Mouse::Left){
            b2Vec2 velocity(100*std::cos(angle), 100*std::sin(angle));
            sf::Vector2f position = {sprite.getPosition().x + (texture.getSize().x/2)*std::cos(angle), sprite.getPosition().y + (texture.getSize().x/2)*std::sin(angle)};


            this->manager->pushEntity(std::make_unique<Bird>(this->manager->getWorld(), 0.2f, position.x/10, position.y/10, velocity, *bird_texture));
        }
    }
}

void Cannon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(sprite, states);
}
