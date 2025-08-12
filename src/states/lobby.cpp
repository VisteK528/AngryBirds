#include "include/states/lobby.hpp"
#include "include/states/adventure.hpp"
#include "include/states/custom.hpp"

Lobby::Lobby(Game& game): AngryBirdsState(game){
    title_ = nullptr;
    adventure_mode_btn_ = nullptr;
    custom_mode_btn_ = nullptr;
    back_btn_ = nullptr;
    initVariables();
}

void Lobby::initVariables() {
    title_ = game_.gui_manager->createText("Select mode:", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    adventure_mode_btn_ = game_.gui_manager->createButton("> Adventure", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    custom_mode_btn_ = game_.gui_manager->createButton("> Custom",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    back_btn_ = game_.gui_manager->createButton("> Back", 20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);

    background_texture_.loadFromFile("textures/menu_background.jpeg");
    background_ = sf::Sprite(background_texture_);
    background_.setColor(sf::Color(255, 255, 255, 180));
    background_.setPosition(0,0);
}

void Lobby::update(const float &) {
    game_.sound_manager->updateVolume();
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    this->adventure_mode_btn_->update(position);
    this->custom_mode_btn_->update(position);
    this->back_btn_->update(position);
}

void Lobby::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());

    if(this->adventure_mode_btn_->handleInput(position, e)){
        game_.addState(std::make_unique<Adventure>(game_), false);
    }

    if(this->custom_mode_btn_->handleInput(position, e)){
        game_.addState(std::make_unique<Custom>(game_), false);
    }

    if(this->back_btn_->handleInput(position, e)){
        quit = true;
    }
}

void Lobby::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_);
    target->draw(*this->title_);
    target->draw(*this->adventure_mode_btn_);
    target->draw(*this->custom_mode_btn_);
    target->draw(*this->back_btn_);
}