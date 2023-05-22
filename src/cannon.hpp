//
// Created by piotr on 5/6/23.
//

#ifndef ANGRYBIRDS_CANNON_HPP
#define ANGRYBIRDS_CANNON_HPP

#include <SFML/Graphics.hpp>
#include "entities/entity_manager.hpp"
#include "entities/birds/bird.hpp"
#include "entities/birds/yellow_bird.hpp"
#include "entities/birds/fat_red_bird.hpp"
#include "entities/birds/grey_bird.hpp"
#include "../box2d/include/box2d/box2d.h"
#include <iostream>

class CannonPowerWidget: public sf::Drawable{
private:
    sf::RectangleShape outline_rectangle_widget;
    sf::RectangleShape fill_rectangle_widget;

    float cannon_max_power = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    void update(float cannon_power, bool cannon_active);
    CannonPowerWidget()=default;
    CannonPowerWidget(float coord_x, float coord_y, float cannon_max_power);
};

class Cannon: public sf::Drawable {
private:
    std::shared_ptr<EntityManager> manager;
    std::vector<std::unique_ptr<Bird>> birds = {};

    sf::Texture hull_texture;
    sf::Texture cannon_texture;
    sf::Sprite cannon_sprite;
    sf::Sprite hull_sprite;
    sf::Vector2f cannon_position;

    unsigned int bird_index = 0;

    float angle = 0;
    float power = 0;
    float power_gain = 4;
    float max_power = 100;
    bool active = true;
    bool loading = false;

    void setBirdsVisualPosition();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Cannon(sf::Vector2f position, std::shared_ptr<EntityManager>);
    bool isActive() const;
    float getPower() const;
    float getMaxPower() const;
    int getBirdsCount() const;
    void setBirds(std::vector<std::unique_ptr<Bird>>& birds);
    void update(sf::Vector2f mouse_position);
    void handleInput(const sf::Event e);
};


#endif //ANGRYBIRDS_CANNON_HPP
