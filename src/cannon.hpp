//
// Created by piotr on 5/6/23.
//

#ifndef ANGRYBIRDS_CANNON_HPP
#define ANGRYBIRDS_CANNON_HPP

#include <SFML/Graphics.hpp>
#include "entities/entity_manager.hpp"
#include "entities/bird.hpp"
#include "../box2d/include/box2d/box2d.h"
#include <iostream>

class Cannon: public sf::Drawable {
private:
    std::shared_ptr<EntityManager> manager;
    std::shared_ptr<sf::Texture> bird_texture;

    sf::Texture hull_texture;
    sf::Texture cannon_texture;
    sf::Sprite cannon_sprite;
    sf::Sprite hull_sprite;
    sf::Vector2f cannon_position;

    float angle = 0;
    float power = 0;
    float power_gain = 4000;
    float max_power = 20000;

    bool active = true;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Cannon(sf::Vector2f position, std::shared_ptr<EntityManager> manager);
    void update(sf::Vector2f mouse_position);
    void handleInput(const sf::Event e);
};


#endif //ANGRYBIRDS_CANNON_HPP
