#include "include/states/custom.hpp"

Custom::Custom(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
               std::shared_ptr<GuiManager> gui_manager, std::shared_ptr<SoundManager> sound_manager): State(
                       std::move(window), std::move(states), std::move(gui_manager),
                       std::move(sound_manager)){
    this->title = nullptr;
    this->level1_btn = nullptr;
    this->level2_btn = nullptr;
    this->level3_btn = nullptr;
    this->level4_btn = nullptr;
    this->level5_btn = nullptr;
    this->back_btn = nullptr;
    initVariables();
}

Custom::~Custom(){

}

void Custom::initVariables() {
    this->title = gui_manager->createText("Select level:", 70, sf::Vector2f(640, 125), ui::ORIGIN::C);

    this->level1_btn = gui_manager->createButton("1", 20, sf::Vector2f(320, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level2_btn = gui_manager->createButton("2", 20, sf::Vector2f(480, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level3_btn = gui_manager->createButton("3", 20, sf::Vector2f(640, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level4_btn = gui_manager->createButton("4", 20, sf::Vector2f(800, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);
    this->level5_btn = gui_manager->createButton("5", 20, sf::Vector2f(960, 400), sf::Vector2f(100, 100), ui::ORIGIN::C);

    this->back_btn = gui_manager->createButton("> Back", 20, sf::Vector2f(1180, 680), sf::Vector2f(160, 40), ui::ORIGIN::C);

    this->background_texture.loadFromFile("textures/menu_background.jpeg");
    this->background = sf::Sprite(background_texture);
    this->background.setColor(sf::Color(255, 255, 255, 180));
    this->background.setPosition(0,0);
}

void Custom::update(const float &) {
    this->sound_manager->updateVolume();
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->level1_btn->update(position);
    this->level2_btn->update(position);
    this->level3_btn->update(position);
    this->level4_btn->update(position);
    this->level5_btn->update(position);
    this->back_btn->update(position);
}

void Custom::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if (this->level1_btn->handleInput(position, e)) {
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/custom/custom_level_0.json"));
    }
    if (this->level2_btn->handleInput(position, e)) {
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/custom/custom_level_1.json"));
    }
    if (this->level3_btn->handleInput(position, e)) {
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/custom/custom_level_2.json"));
    }
    if (this->level4_btn->handleInput(position, e)) {
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/custom/custom_level_3.json"));
    }
    if (this->level5_btn->handleInput(position, e)) {
        this->states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, this->sound_manager,"data/custom/custom_level_4.json"));
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

void Custom::init() {

}