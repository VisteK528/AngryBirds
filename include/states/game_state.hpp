#ifndef ANGRYBIRDS_GAME_STATE_HPP
#define ANGRYBIRDS_GAME_STATE_HPP

// Standard libraries
#include <iostream>
#include <string>
#include <fstream>

// Box2D
#include "box2d/include/box2d/box2d.h"
#include "include/contact_listener.hpp"

// States
#include "state.hpp"
#include "win.hpp"
#include "loose.hpp"

//Entities
#include "include/entities/birds/bird.hpp"
#include "include/entities/boxes/box.hpp"
#include "include/entities/boxes/wood/wood.hpp"
#include "include/entities/boxes/wood/wood3x1.hpp"
#include "include/entities/boxes/stone/stone.hpp"
#include "include/entities/boxes/stone/stone3x1.hpp"
#include "include/entities/boxes/glass/glass.hpp"
#include "include/entities/boxes/glass/glass3x1.hpp"
#include "src/entities/pigs/pig.hpp"
#include "src/entities/pigs/basic_pig/basic_pig.hpp"
#include "src/entities/pigs/armored_pig/armored_pig.hpp"
#include "include/entities/entity_manager.hpp"
#include "include/cannon.hpp"
#include "include/entities/birds/yellow_bird.hpp"
#include "include/entities/birds/fat_red_bird.hpp"
#include "include/entities/birds/grey_bird.hpp"

// Factories
#include "include/entities/factories/bird_factory.hpp"
#include "include/entities/factories/box_factory.hpp"
#include "include/entities/factories/pig_factory.hpp"

// Utilities
#include "include/textures.hpp"
#include "include/json.hpp"
#include "include/exceptions.hpp"

using json = nlohmann::json;

class GameState: public State {
private:
    typedef enum{WIN, LOOSE} RESULT;

    RESULT result;
    bool running = false;
    int score = 0;

    std::string level_path;
    b2Vec2 gravity;
    std::shared_ptr<b2World> world;
    std::shared_ptr<EntityManager> entity_manager;
    std::unique_ptr<Cannon> cannon;
    CannonPowerWidget cannon_power_widget;
    ContactListener contact_listener;

    std::unique_ptr<ui::Text> score_text;

    sf::Sprite background;
    std::unordered_map<TEXTURE_TYPE, std::vector<sf::Texture>> entities_textures;
    std::unordered_map<BACKGROUNDS, sf::Texture> background_textures;

    const float SCALE = 10.0f;

    std::vector<std::unique_ptr<Bird>> loadWorld(const std::string& level_path);
    void setWall(int x, int y, int w, int h);
    void initWorld();

public:
    GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager, std::string level_path);
    ~GameState();

    void init() override;
    void update(const float& dt) override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //ANGRYBIRDS_GAME_STATE_HPP
