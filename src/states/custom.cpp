#include "include/states/custom.hpp"
#include "include/states/game_state.hpp"
#include <format>

Custom::Custom(Game& game): AngryBirdsState(game){
    title = nullptr;
    level1_btn = nullptr;
    level2_btn = nullptr;
    level3_btn = nullptr;
    level4_btn = nullptr;
    level5_btn = nullptr;
    back_btn = nullptr;
    initVariables();
}

void Custom::initVariables() {
    this->title = game_.gui_manager->createText("Select level:", 70, sf::Vector2f(640, 125), ui::ORIGIN::C);

    this->level1_btn = game_.gui_manager->createButton("1", 20, sf::Vector2f(320, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level2_btn = game_.gui_manager->createButton("2", 20, sf::Vector2f(480, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level3_btn = game_.gui_manager->createButton("3", 20, sf::Vector2f(640, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level4_btn = game_.gui_manager->createButton("4", 20, sf::Vector2f(800, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level5_btn = game_.gui_manager->createButton("5", 20, sf::Vector2f(960, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);

    this->back_btn = game_.gui_manager->createButton("> Back", 20, sf::Vector2f(1180, 680), sf::Vector2f(160, 40), ui::ORIGIN::C);

    this->background_texture.loadFromFile("textures/menu_background.jpeg");
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void Custom::update(const float &) {
    game_.sound_manager->updateVolume();
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    this->level1_btn->update(position);
    this->level2_btn->update(position);
    this->level3_btn->update(position);
    this->level4_btn->update(position);
    this->level5_btn->update(position);
    this->back_btn->update(position);

    if(load_next_level){
        load_next_level = false;
        if(current_level_number < 4){
            current_level_number++;
            game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
        }
    }

    if(retry_level){
        retry_level = false;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
    }
}

void Custom::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());

    if (this->level1_btn->handleInput(position, e)) {
        game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
        current_level_number = 0;
    }
    else if (this->level2_btn->handleInput(position, e)) {
        game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
        current_level_number = 1;
    }
    else if (this->level3_btn->handleInput(position, e)) {
        game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
        current_level_number = 2;
    }
    else if (this->level4_btn->handleInput(position, e)) {
        game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
        current_level_number = 3;
    }
    else if (this->level5_btn->handleInput(position, e)) {
        game_.addState(std::make_unique<GameState>(game_, std::format("data/custom/custom_level_{}.json", std::to_string(current_level_number))));
        current_level_number = 4;
    }
    if (this->back_btn->handleInput(position, e)) {
        quit = true;
    }
}

void Custom::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*this->title);
    target->draw(*this->level1_btn);
    target->draw(*this->level2_btn);
    target->draw(*this->level3_btn);
    target->draw(*this->level4_btn);
    target->draw(*this->level5_btn);
    target->draw(*this->back_btn);
}

void Custom::onEnter() {
    if(game_.sound_manager->getBackgroundMusic().getStatus() == sf::Music::Stopped){
        game_.sound_manager->setBackgroundMusic("sounds/Angry-Birds-Theme.wav");
        game_.sound_manager->getBackgroundMusic().setLoop(true);
        game_.sound_manager->getBackgroundMusic().play();
    }
}