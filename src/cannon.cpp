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

    sf::Image image;
    image.create(200, 50, sf::Color(255, 0, 0, 255));
    texture.loadFromImage(image);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(position);
    sprite.setTexture(texture);

    cannon_sprite.setOrigin(cannon_texture.getSize().x/2-20, cannon_texture.getSize().y / 2);
    cannon_position = {position.x+40, position.y-hull_texture.getSize().y/2-cannon_texture.getSize().y/2+25};
    cannon_sprite.setPosition(cannon_position);
    cannon_sprite.setTexture(cannon_texture);

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

            std::unique_ptr<YellowBird> bird = std::make_unique<YellowBird>(this->manager->getWorld(), position.x/10, position.y/10);

            bird->applyForce(velocity);
            this->manager->pushEntity(std::move(bird));
            power = 0;

            // TODO Commented only for testing purposes, uncomment before release
            active = false;
        }
    }
}

void Cannon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(cannon_sprite, states);
    target.draw(hull_sprite, states);
}
