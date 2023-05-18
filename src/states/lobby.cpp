#include "lobby.hpp"

Lobby::Lobby(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager): State(window, states){
    this->gui_manager = std::move(gui_manager);
    this->title = nullptr;
    this->adventure_mode_btn = nullptr;
    this->custom_mode_btn = nullptr;
    this->back_btn = nullptr;
    initVariables();
}

Lobby::~Lobby(){

}

void Lobby::initVariables() {
    this->title = gui_manager->createText("Select mode:", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    this->adventure_mode_btn = gui_manager->createButton("> Adventure", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->custom_mode_btn = gui_manager->createButton("> Custom",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->back_btn = gui_manager->createButton("> Back", 20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);
}

void Lobby::update(const float &) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->adventure_mode_btn->update(position);
    this->custom_mode_btn->update(position);
    this->back_btn->update(position);
}

void Lobby::handleEvent(const sf::Event &e) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->adventure_mode_btn->handleInput(position, e)){
        this->states->push(std::make_unique<Adventure>(this->window, this->states, this->gui_manager));
    }

    if(this->custom_mode_btn->handleInput(position, e)){
        this->states->push(std::make_unique<Custom>(this->window, this->states, this->gui_manager));
    }

    if(this->back_btn->handleInput(position, e)){
        this->states->pop();
    }
}

void Lobby::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(*this->title);
    target->draw(*this->adventure_mode_btn);
    target->draw(*this->custom_mode_btn);
    target->draw(*this->back_btn);
}

void Lobby::init() {

}