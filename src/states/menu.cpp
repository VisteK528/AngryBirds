//
// Created by piotr on 5/4/23.
//

#include "menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager): State(window, states){
    this->gui_manager = std::move(gui_manager);
    this->title = nullptr;
    this->start_btn = nullptr;
    this->editor_btn = nullptr;
    this->about_btn = nullptr;
    this->exit_btn = nullptr;
    initVariables();
}

Menu::~Menu(){

}

void Menu::initVariables() {
    this->title = gui_manager->createText("Angry Birds", 70, sf::Vector2f(640, 250), ui::ORIGIN::C);
    this->start_btn = gui_manager->createButton("> Start", 20, sf::Vector2f(640, 400), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->editor_btn = gui_manager->createButton("> Editor",20, sf::Vector2f(640, 480), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->about_btn = gui_manager->createButton("> About", 20, sf::Vector2f(640, 560), sf::Vector2f(250, 60), ui::ORIGIN::C);
    this->exit_btn = gui_manager->createButton("> Exit",20, sf::Vector2f(640, 640), sf::Vector2f(250, 60), ui::ORIGIN::C);
}

void Menu::update(const float &dt) {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->start_btn->update(position)){
        this->states->push(std::make_unique<GameState>(this->window, this->states));
    }

    if(this->editor_btn->update(position)){

    }

    if(this->about_btn->update(position)){

    }

    if(this->exit_btn->update(position)){
        quit = true;
    }
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(*title);
    target->draw(*start_btn);
    target->draw(*editor_btn);
    target->draw(*about_btn);
    target->draw(*exit_btn);
}

void Menu::init() {

}
