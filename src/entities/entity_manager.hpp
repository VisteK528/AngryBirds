//
// Created by piotr on 5/5/23.
//

#ifndef ANGRYBIRDS_ENTITY_MANAGER_HPP
#define ANGRYBIRDS_ENTITY_MANAGER_HPP

#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include "../../box2d/include/box2d/box2d.h"

class EntityManager {
private:
    std::shared_ptr<b2World> world;
public:
    const std::shared_ptr<b2World> &getWorld() const;

private:
    std::vector<std::unique_ptr<Entity>> entities;
public:
    EntityManager(std::shared_ptr<b2World> world);
    void update();
    void render(std::shared_ptr<sf::RenderTarget> target);
    void pushEntity(std::unique_ptr<Entity> entity);

};


#endif //ANGRYBIRDS_ENTITY_MANAGER_HPP
