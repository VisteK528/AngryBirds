//
// Created by piotr on 5/5/23.
//

#include "entity_manager.hpp"

EntityManager::EntityManager(std::shared_ptr<b2World> world) {
    this->world = std::move(world);
}

void EntityManager::pushEntity(std::unique_ptr<Entity> entity) {
    this->entities.push_back(std::move(entity));
}

void EntityManager::update() {
    for(const auto& entity: entities){
        entity->update();
        if(entity->getDestroyed()){
            world->DestroyBody(entity->getBody());
        }
    }
    this->entities.erase(std::remove_if(entities.begin(), entities.end(), [&](const auto& e){return e->getDestroyed() == true;}), this->entities.end());
}

void EntityManager::render(std::shared_ptr<sf::RenderTarget> target) {
    for(const auto& entity: entities){
        target->draw(*entity);
    }
}