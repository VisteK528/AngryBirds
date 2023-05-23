//
// Created by piotr on 5/5/23.
//

#include "entity_manager.hpp"
#include <iostream>

EntityManager::EntityManager(std::shared_ptr<b2World> world) {
    this->world = std::move(world);
}

void EntityManager::pushEntity(std::unique_ptr<Entity> entity) {
    if(entity->getType().main_type == TYPE_DATA::BIRD){
        bird_active = true;
    }
    this->entities.push_back(std::move(entity));
}

void EntityManager::update() {
    bool start_counting = false;
    for(const auto& entity: entities){
        entity->update();
        if(entity->getDestroyed()){
            world->DestroyBody(entity->getBody());
            if(entity->getType().main_type == TYPE_DATA::BIRD){
                bird_active = false;
            }
            else {
                start_counting = true;
                updateScore(entity->getScore());
                std::cout << "Score: " << getCurrentScore() << std::endl;
            }
        }
    }

    this->entities.erase(std::remove_if(entities.begin(), entities.end(), [&](const auto& e){return e->getDestroyed() == true;}), this->entities.end());

    if(start_counting){
        if(CountPigs() == 0){
            m_win = true;
        }
        else{
            std::cout << "Pigs: " << CountPigs() << std::endl;
        }
    }
}

void EntityManager::render(std::shared_ptr<sf::RenderTarget> target) {
    for(const auto& entity: entities){
        target->draw(*entity);
    }
}

const std::shared_ptr<b2World> &EntityManager::getWorld() const {
    return world;
}

bool EntityManager::isBirdActive() const {
    return bird_active;
}

int EntityManager::getCurrentScore() const {
    return current_score;
}

void EntityManager::updateScore(int score) {
    current_score += score;
}

int EntityManager::CountPigs() const {
    return (int)std::count_if(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& e){return e->getType().main_type == TYPE_DATA::PIG;});
}

int EntityManager::CountBirds() const {
    return (int)std::count_if(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& e){return e->getType().main_type == TYPE_DATA::BIRD;});
}

void EntityManager::setBirds(int birds) {
    m_birds = birds;

    if (m_birds == 0 && CountPigs() != 0 && CountBirds() == 0) {
        m_lose = true;
    }
}

bool EntityManager::CheckForWin() const {
    return m_win;
}

bool EntityManager::CheckForLose() const {
    return m_lose;
}