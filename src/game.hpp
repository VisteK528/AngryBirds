//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_GAME_HPP
#define ANGRYBIRDS_GAME_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include "states//state.hpp"
#include "states/game_state.hpp"

class Game {
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
    std::unique_ptr<sf::View> view;
    sf::Event e;

    sf::Font font;
    sf::Texture app_icon_texture;

    const sf::Vector2u window_dimensions = {1400, 600};     // 21:9 aspect ratio

    float dt;
    sf::Clock dt_clock;

    void setIcon();
    void loadTextures();
    void updateDt();
    void updateEvents();
    void update();
    void render();
public:
    Game();
    ~Game();
    void run();
};


#endif //ANGRYBIRDS_GAME_HPP
