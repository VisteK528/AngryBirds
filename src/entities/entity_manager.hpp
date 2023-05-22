//
// Created by piotr on 5/5/23.
//

#ifndef ANGRYBIRDS_ENTITY_MANAGER_HPP
#define ANGRYBIRDS_ENTITY_MANAGER_HPP

#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include "../../box2d/include/box2d/box2d.h"

/* TODO Create methods for checking if all birds and pigs are destroyed (separately)
 * TODO Make bird's action available only for the last bird
 * */

class EntityManager {
private:
    std::shared_ptr<b2World> world;
    std::vector<std::unique_ptr<Entity>> entities;
    bool bird_active = false;

    int current_score = 0;
    void updateScore(int score);
    int m_birds;
    bool m_win = false;
    bool m_lose = false;

public:
    EntityManager(std::shared_ptr<b2World> world);
    bool isBirdActive() const;
    void update();
    void setBirds(int birds);
    void render(std::shared_ptr<sf::RenderTarget> target);
    void pushEntity(std::unique_ptr<Entity> entity);
    const std::shared_ptr<b2World> &getWorld() const;

    int getCurrentScore() const;
    bool CheckForWin() const;
    bool CheckForLose() const;
    int CountPigs() const;
    int CountBirds() const;
};


#endif //ANGRYBIRDS_ENTITY_MANAGER_HPP
