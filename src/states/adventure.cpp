#include "include/states/adventure.hpp"
#include "include/states/game_state.hpp"
#include <format>

Adventure::Adventure(Game& game): AngryBirdsState(game){
    title = nullptr;
    level1_btn = nullptr;
    level2_btn = nullptr;
    level3_btn = nullptr;
    level4_btn = nullptr;
    level5_btn = nullptr;
    level6_btn = nullptr;
    level7_btn = nullptr;
    level8_btn = nullptr;
    level9_btn = nullptr;
    level10_btn = nullptr;
    back_btn = nullptr;
    initVariables();
}

void Adventure::initVariables() {
    title = game_.gui_manager->createText("Select level:", 70, sf::Vector2f(640, 125), ui::ORIGIN::C);

    level1_btn = game_.gui_manager->createButton("1", 20, sf::Vector2f(160, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level2_btn = game_.gui_manager->createButton("2", 20, sf::Vector2f(320, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level3_btn = game_.gui_manager->createButton("3", 20, sf::Vector2f(480, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level4_btn = game_.gui_manager->createButton("4", 20, sf::Vector2f(640, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level5_btn = game_.gui_manager->createButton("5", 20, sf::Vector2f(800, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level6_btn = game_.gui_manager->createButton("6", 20, sf::Vector2f(960, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level7_btn = game_.gui_manager->createButton("7", 20, sf::Vector2f(1120, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level8_btn = game_.gui_manager->createButton("8", 20, sf::Vector2f(160, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level9_btn = game_.gui_manager->createButton("9", 20, sf::Vector2f(320, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level10_btn = game_.gui_manager->createButton("10", 20, sf::Vector2f(480, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level11_btn = game_.gui_manager->createButton("11", 20, sf::Vector2f(640, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level12_btn = game_.gui_manager->createButton("12", 20, sf::Vector2f(800, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level13_btn = game_.gui_manager->createButton("13", 20, sf::Vector2f(960, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    level14_btn = game_.gui_manager->createButton("14", 20, sf::Vector2f(1120, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);

    this->back_btn = game_.gui_manager->createButton("> Back", 20, sf::Vector2f(1180, 680), sf::Vector2f(160, 40), ui::ORIGIN::C);

    this->background_texture.loadFromFile("textures/menu_background.jpeg");
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void Adventure::update(const float &) {
    game_.sound_manager->updateVolume();
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    level1_btn->update(position);
    level2_btn->update(position);
    level3_btn->update(position);
    level4_btn->update(position);
    level5_btn->update(position);
    level6_btn->update(position);
    level7_btn->update(position);
    level8_btn->update(position);
    level9_btn->update(position);
    level10_btn->update(position);
    level11_btn->update(position);
    level12_btn->update(position);
    level13_btn->update(position);
    level14_btn->update(position);
    back_btn->update(position);

    if(load_next_level){
        load_next_level = false;
        if(current_level_number < 14){
            current_level_number++;
            game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
        }
    }

    if(retry_level){
        retry_level = false;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }
}

void Adventure::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());

    if(this->level1_btn->handleInput(position, e)){
        current_level_number = 1;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));

    }

    if(this->level2_btn->handleInput(position, e)){
        current_level_number = 2;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level3_btn->handleInput(position, e)){
        current_level_number = 3;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level4_btn->handleInput(position, e)){
        current_level_number = 4;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level5_btn->handleInput(position, e)){
        current_level_number = 5;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level6_btn->handleInput(position, e)){
        current_level_number = 6;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level7_btn->handleInput(position, e)){
        current_level_number = 7;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level8_btn->handleInput(position, e)){
        current_level_number = 8;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level9_btn->handleInput(position, e)){
        current_level_number = 9;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level10_btn->handleInput(position, e)){
        current_level_number = 10;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level11_btn->handleInput(position, e)){
        current_level_number = 11;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level12_btn->handleInput(position, e)){
        current_level_number = 12;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level13_btn->handleInput(position, e)){
        current_level_number = 13;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->level14_btn->handleInput(position, e)){
        current_level_number = 14;
        game_.addState(std::make_unique<GameState>(game_, std::format("data/adventure/adventure_level_{}.json", std::to_string(current_level_number))));
    }

    if(this->back_btn->handleInput(position, e)){
        quit = true;
    }

}

void Adventure::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background);
    target->draw(*this->title);
    target->draw(*this->level1_btn);
    target->draw(*this->level2_btn);
    target->draw(*this->level3_btn);
    target->draw(*this->level4_btn);
    target->draw(*this->level5_btn);
    target->draw(*this->level6_btn);
    target->draw(*this->level7_btn);
    target->draw(*this->level8_btn);
    target->draw(*this->level9_btn);
    target->draw(*this->level10_btn);
    target->draw(*this->level11_btn);
    target->draw(*this->level12_btn);
    target->draw(*this->level13_btn);
    target->draw(*this->level14_btn);
    target->draw(*this->back_btn);
}

void Adventure::onEnter() {
    if(game_.sound_manager->getBackgroundMusic().getStatus() == sf::Music::Stopped){
        game_.sound_manager->setBackgroundMusic("sounds/Angry-Birds-Theme.wav");
        game_.sound_manager->getBackgroundMusic().setLoop(true);
        game_.sound_manager->getBackgroundMusic().play();
    }
}