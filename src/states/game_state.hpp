//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_GAME_STATE_HPP
#define ANGRYBIRDS_GAME_STATE_HPP

#include "state.hpp"
#include "../../box2d/include/box2d/box2d.h"
#include "../entities/bird.hpp"
#include "../entities/box.hpp"
#include <iostream>
#include <string>
#include "../contact_listener.hpp"
#include "../entities/entity_manager.hpp"

class GameState: public State {
private:
    b2Vec2 gravity;
    std::shared_ptr<b2World> world;
    std::unique_ptr<EntityManager> entity_manager;
    ContactListener contact_listener;

    sf::Sprite background;
    std::vector<sf::Texture> textures;

    const float SCALE = 10.0f;
    const float DEG = 57.29577f;

    void setWall(int x, int y, int w, int h);
    void initWorld();
public:
    GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
    ~GameState();

    void init() override;
    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_GAME_STATE_HPP
