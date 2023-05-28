#include "include/states/adventure.hpp"

Adventure::Adventure(std::shared_ptr<sf::RenderWindow> window,std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
                     std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager): State(
                             std::move(window), std::move(states), std::move(gui_manager),
                             std::move(sound_manager)){
    this->title = nullptr;
    this->level1_btn = nullptr;
    this->level2_btn = nullptr;
    this->level3_btn = nullptr;
    this->level4_btn = nullptr;
    this->level5_btn = nullptr;
    this->level6_btn = nullptr;
    this->level7_btn = nullptr;
    this->level8_btn = nullptr;
    this->level9_btn = nullptr;
    this->level10_btn = nullptr;
    this->back_btn = nullptr;
    initVariables();
}

Adventure::~Adventure(){

}

void Adventure::initVariables() {
    this->title = gui_manager->createText("Select level:", 70, sf::Vector2f(640, 125), ui::ORIGIN::C);

    this->level1_btn = gui_manager->createButton("1", 20, sf::Vector2f(160, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level2_btn = gui_manager->createButton("2", 20, sf::Vector2f(320, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level3_btn = gui_manager->createButton("3", 20, sf::Vector2f(480, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level4_btn = gui_manager->createButton("4", 20, sf::Vector2f(640, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level5_btn = gui_manager->createButton("5", 20, sf::Vector2f(800, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level6_btn = gui_manager->createButton("6", 20, sf::Vector2f(960, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level7_btn = gui_manager->createButton("7", 20, sf::Vector2f(1120, 300), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level8_btn = gui_manager->createButton("8", 20, sf::Vector2f(160, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level9_btn = gui_manager->createButton("9", 20, sf::Vector2f(320, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level10_btn = gui_manager->createButton("10", 20, sf::Vector2f(480, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level11_btn = gui_manager->createButton("11", 20, sf::Vector2f(640, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level12_btn = gui_manager->createButton("12", 20, sf::Vector2f(800, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level13_btn = gui_manager->createButton("13", 20, sf::Vector2f(960, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level14_btn = gui_manager->createButton("14", 20, sf::Vector2f(1120, 460), sf::Vector2f(100, 100), ui::ORIGIN::C);

    this->back_btn = gui_manager->createButton("> Back", 20, sf::Vector2f(1180, 680), sf::Vector2f(160, 40), ui::ORIGIN::C);

    this->background_texture.loadFromFile("textures/menu_background.jpeg");
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void Adventure::update(const float &) {
    this->sound_manager->updateVolume();
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->level1_btn->update(position);
    this->level2_btn->update(position);
    this->level3_btn->update(position);
    this->level4_btn->update(position);
    this->level5_btn->update(position);
    this->level6_btn->update(position);
    this->level7_btn->update(position);
    this->level8_btn->update(position);
    this->level9_btn->update(position);
    this->level10_btn->update(position);
    this->level11_btn->update(position);
    this->level12_btn->update(position);
    this->level13_btn->update(position);
    this->level14_btn->update(position);
    this->back_btn->update(position);

    if(load_next_level){
        load_next_level = false;
        if(current_level_number < 14){
            current_level_number++;
            this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_"+std::to_string(current_level_number)));
        }
    }

    if(retry_level){
        retry_level = false;
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_"+std::to_string(current_level_number)));
    }
}

void Adventure::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->level1_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_1"));
        current_level_number = 1;
    }

    if(this->level2_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_2"));
        current_level_number = 2;
    }

    if(this->level3_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_3"));
        current_level_number = 3;
    }

    if(this->level4_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_4"));
        current_level_number = 4;
    }

    if(this->level5_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_5"));
        current_level_number = 5;
    }

    if(this->level6_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_6"));
        current_level_number = 6;
    }

    if(this->level7_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_7"));
        current_level_number = 7;
    }

    if(this->level8_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_8"));
        current_level_number = 8;
    }

    if(this->level9_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_9"));
        current_level_number = 9;
    }

    if(this->level10_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_10"));
        current_level_number = 10;
    }

    if(this->level11_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_11"));
        current_level_number = 11;
    }

    if(this->level12_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_12"));
        current_level_number = 12;
    }

    if(this->level13_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_13"));
        current_level_number = 13;
    }

    if(this->level14_btn->handleInput(position, e)){
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/adventure/adventure_level_14"));
        current_level_number = 14;
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

void Adventure::init() {

}