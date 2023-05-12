//
// Created by piotr on 5/6/23.
//

#ifndef ANGRYBIRDS_CANNON_HPP
#define ANGRYBIRDS_CANNON_HPP

#include <SFML/Graphics.hpp>
#include "entities/entity_manager.hpp"
#include "entities/bird.hpp"
#include "../box2d/include/box2d/box2d.h"

class Cannon: public sf::Drawable {
private:
    std::shared_ptr<EntityManager> manager;
    std::shared_ptr<b2World> world;
    std::shared_ptr<sf::Texture> bird_texture;
    sf::Texture texture;
    sf::Sprite sprite;

    float angle = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Cannon(sf::Vector2f position, std::shared_ptr<EntityManager> manager);
    void update(sf::Vector2i mouse_position);
    void handleInput(const sf::Event e);
};


#endif //ANGRYBIRDS_CANNON_HPP
