#include "include/states/menu.hpp"
#include "include/states/lobby.hpp"
#include "include/states/editor_state.hpp"
#include "include/states/about.hpp"

Menu::Menu(Game& game): AngryBirdsState(game){
    title_ = nullptr;
    start_btn_ = nullptr;
    editor_btn_ = nullptr;
    about_btn_ = nullptr;
    exit_btn_ = nullptr;
    initVariables();
}

void Menu::initVariables() {
    title_ = game_.gui_manager->createText("Angry Birds", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    start_btn_ = game_.gui_manager->createButton("> Start", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    editor_btn_ = game_.gui_manager->createButton("> Editor",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    about_btn_ = game_.gui_manager->createButton("> About", 20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);
    exit_btn_ = game_.gui_manager->createButton("> Exit",20, sf::Vector2f(640, 640), sf::Vector2f(250, 60), ui::ORIGIN::C);

    game_.sound_manager->setBackgroundMusic("sounds/Angry-Birds-Theme.wav");
    game_.sound_manager->getBackgroundMusic().setLoop(true);
    game_.sound_manager->getBackgroundMusic().play();

    background_texture_.loadFromFile("textures/menu_background.jpeg");
    background_ = sf::Sprite(background_texture_);
    background_.setColor(sf::Color(255, 255, 255, 180));
    background_.setPosition(0,0);
}

void Menu::update(const float &) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());
    game_.sound_manager->updateVolume();
    start_btn_->update(position);
    editor_btn_->update(position);
    about_btn_->update(position);
    exit_btn_->update(position);
}

void Menu::handleEvent(const sf::Event &e) {
    sf::Vector2f position = game_.window->mapPixelToCoords(sf::Mouse::getPosition(*game_.window), game_.window->getView());

    if(this->start_btn_->handleInput(position, e)){
        game_.addState(std::make_unique<Lobby>(game_), false);
    }

    if(this->editor_btn_->handleInput(position, e)){
        game_.addState(std::make_unique<EditorState>(game_), false);
    }

    if(this->about_btn_->handleInput(position, e)){
        game_.addState(std::make_unique<About>(game_), false);
    }

    if(this->exit_btn_->handleInput(position, e)){
        quit = true;
    }
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(background_);
    target->draw(*title_);
    target->draw(*start_btn_);
    target->draw(*editor_btn_);
    target->draw(*about_btn_);
    target->draw(*exit_btn_);
}

void Menu::onEnter() {
    if(game_.sound_manager->getBackgroundMusic().getStatus() == sf::Music::Stopped){
        game_.sound_manager->setBackgroundMusic("sounds/Angry-Birds-Theme.wav");
        game_.sound_manager->getBackgroundMusic().setLoop(true);
        game_.sound_manager->getBackgroundMusic().play();
    }
}
