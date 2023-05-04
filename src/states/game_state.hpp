//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_GAME_STATE_HPP
#define ANGRYBIRDS_GAME_STATE_HPP

#include "state.hpp"
#include "../../box2d/include/box2d/box2d.h"
#include "../bird.hpp"

class GameState: public State {
private:
    b2Vec2 gravity;
    std::shared_ptr<b2World> world;
    Bird bird;
    Bird bird2;
    Bird bird3;
    sf::Sprite background;
    std::vector<sf::Texture> textures;

    const float SCALE = 30.0f;
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
