//
// Created by piotr on 5/4/23.
//

#ifndef ANGRYBIRDS_GAME_STATE_HPP
#define ANGRYBIRDS_GAME_STATE_HPP

#include "state.hpp"
#include "../../box2d/include/box2d/box2d.h"
#include "../entities/birds/bird.hpp"
#include "../entities/boxes/box.hpp"
#include "../entities/boxes/wood/wood.hpp"
#include "../entities/boxes/wood/wood3x1.hpp"
#include "../entities/boxes/stone/stone.hpp"
#include "../entities/boxes/stone/stone3x1.hpp"
#include "../entities/boxes/glass/glass.hpp"
#include "../entities/boxes/glass/glass3x1.hpp"
#include "../entities/pigs/pig.hpp"
#include "../entities/pigs/basic_pig/basic_pig.hpp"
#include "../entities/pigs/armored_pig//armored_pig.hpp"
#include <iostream>
#include <string>
#include "../contact_listener.hpp"
#include "../entities/entity_manager.hpp"
#include "../cannon.hpp"
#include "../entities/birds/yellow_bird.hpp"
#include "../entities/birds/fat_red_bird.hpp"
#include "../entities/birds/grey_bird.hpp"
#include "../exceptions.hpp"
#include "../entities/factories/bird_factory.hpp"
#include "../entities/factories/box_factory.hpp"
#include "../entities/factories/pig_factory.hpp"
#include "../textures.hpp"
#include "../../include/json.hpp"
#include <fstream>

using json = nlohmann::json;

// TODO Add the possibility to load the game from file
class GameState: public State {
private:
    b2Vec2 gravity;
    std::shared_ptr<b2World> world;
    std::shared_ptr<EntityManager> entity_manager;
    std::unique_ptr<Cannon> cannon;
    CannonPowerWidget cannon_power_widget;
    ContactListener contact_listener;

    sf::Sprite background;
    std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>> entities_textures;
    std::vector<sf::Texture> textures;

    const float SCALE = 10.0f;

    std::vector<std::unique_ptr<Bird>> loadWorld(const std::string& level_path);
    void loadTextures();
    void setWall(int x, int y, int w, int h);
    void initWorld();
public:
    GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
    ~GameState();

    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_GAME_STATE_HPP
